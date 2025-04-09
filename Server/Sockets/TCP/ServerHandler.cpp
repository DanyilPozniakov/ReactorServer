//
// Created by pozni on 3/15/2025.
//

#include <iostream>

#include "ClientHandler.h"
#include "ServerHandler.h"

ServerHandler::ServerHandler(TaskManager* reactor)
    : m_taskManager(reactor)
{

}

ServerHandler::~ServerHandler()
{
}

void ServerHandler::HandleAccept(SOCKET socket, ISocket* reactor)
{
    sockaddr_in clientInfo;
    int addrLen = sizeof(clientInfo);
    SOCKET clientSock = accept(socket, (sockaddr*)&clientInfo, &addrLen);
    if (clientSock == INVALID_SOCKET) {
        std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
        return;
    }

    //Creating and save a connection info
    char    host[NI_MAXHOST];
    int     port = ntohs(clientInfo.sin_port);
    inet_ntop(AF_INET, &clientInfo.sin_addr, host, NI_MAXHOST);


    std::cout << "[SERVER  E_HANDLER] New connection accepted: " << host << " on port: " << port << std::endl;
    u_long mode = 1;
    ioctlsocket(clientSock, FIONBIO, &mode); //Set socket to non-blocking mode
    reactor->RegisterHandler(clientSock, new ClientHandler(m_taskManager));
}

void ServerHandler::HandleDisconnect(SOCKET socket, ISocket* reactor)
{
    //TODO:
}

void ServerHandler::HandleRead(SOCKET socket, ISocket* reactor)
{
    std::cerr << "[SERVER  E_HANDLER] ServerHandler::HandleRead is not implemented" << std::endl;
}

void ServerHandler::HandleWrite(SOCKET socket, ISocket* reactor)
{
    std::cerr << "[SERVER  E_HANDLER] ServerHandler::HandleWrite is not implemented" << std::endl;
}

void ServerHandler::HandleError(SOCKET socket, ISocket* reactor)
{
    std::cout << "[SERVER  E_HANDLER] ServerHandler::HandleError is not implemented" << std::endl;
}

bool ServerHandler::HasDataToParse()
{
    std::cout << "[SERVER  E_HANDLER] ServerHandler::HasDataToParse is not implemented" << std::endl;
    return false;
}

bool ServerHandler::HasDataToSend()
{
    std::cout << "[SERVER  E_HANDLER] ServerHandler::HasDataToSend is not implemented" << std::endl;

    return false;
}
