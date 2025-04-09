//
// Created by pozni on 3/16/2025.
//

#include <mutex>
#include <condition_variable>
#include <iostream>
#include "ClientHandler.h"
#include "../TaskManager.h"

namespace
{
std::mutex m_receivedDataMutex;
std::mutex m_dataToSendMutex;
 std::condition_variable m_receivedDataCV;
std::condition_variable m_dataToSendCV;
}


ClientHandler::ClientHandler(TaskManager* taskManager)
    : m_taskManager(taskManager)
{
    taskManager->AddConnection(this);
}

ClientHandler::~ClientHandler()
{
}


void ClientHandler::HandleRead(SOCKET socket, ISocket* reactor)
{
    int result = recv(socket, m_readBuffer.data(), DEFAULT_BUFFER_SIZE, 0);
    if (result == SOCKET_ERROR)
    {
        if (WSAGetLastError() == WSAECONNRESET)
        {
            std::cerr << "[CLIENT HANDLER][ERROR] HandleRead() -> connection reset by peer " << std::endl;
            reactor->RemoveHandler(socket);
            return;
        }
        std::cerr << "[CLIENT HANDLER] HandleRead() -> recv failed with error: " << WSAGetLastError() << std::endl;
    }
    else if (result == 0)
    {
        std::cerr << "[CLIENT HANDLER] HandleRead() -> connection closed! " << std::endl;
        reactor->RemoveHandler(socket);
    }
    else if (result > 0)
    {
        std::string data(m_readBuffer.data(), result);
        {
            std::lock_guard lock(m_receivedDataMutex);
            m_receivedData.push(data);
        }
    }
    // PUSH TO PARSER AND QUEUE
}

void ClientHandler::HandleWrite(SOCKET socket, ISocket* reactor)
{
    if(HasDataToSend())
    {
        std::string data = GetDataToSend();
        int result = send(socket, data.c_str(), data.size(), 0);
        if (result == SOCKET_ERROR)
        {
            std::cerr << "[CLIENT HANDLER] HandleWrite() -> send failed with error: " << WSAGetLastError() << std::endl;
        }
        else if(result > 0)
        {
            std::cout << "[CLIENT HANDLER] HandleWrite() -> sent " << result << " bytes" << std::endl;
        }
    }
}

void ClientHandler::HandleError(SOCKET socket, ISocket* reactor)
{
    std::cerr << "[CLIENT HANDLER] HandleError() -> error on socket: " << socket << std::endl;
}

bool ClientHandler::HasDataToSend()
{
    return !m_dataToSend.empty();
}

bool ClientHandler::HasDataToParse()
{
    return !m_receivedData.empty();
}

void ClientHandler::AddDataToSend(std::string data)
{
    std::lock_guard lock(m_dataToSendMutex);
    m_dataToSend.push(std::move(data));
}

std::string ClientHandler::GetDataToSend()
{
    std::string data;
    {
        std::lock_guard lock(m_dataToSendMutex);
        if (!m_dataToSend.empty())
        {
            data = m_dataToSend.front();
            m_dataToSend.pop();
        }
    }
    return data;
}

std::string ClientHandler::GetDataToParse()
{
    std::string data;
    {
        std::lock_guard lock(m_receivedDataMutex);
        if (!m_receivedData.empty())
        {
            data = m_receivedData.front();
            m_receivedData.pop();
        }
    }
    return data;
}

void ClientHandler::SetBufferSizes(int readSize, int writeSize)
{
}
