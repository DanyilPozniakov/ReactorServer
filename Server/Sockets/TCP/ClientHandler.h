//
// Created by pozni on 3/16/2025.
//

#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H


#include <winsock2.h>
#include <chrono>
#include <queue>

#include <IEventHandler.h>
#include "ISocket.h"
#include <array>


class TaskManager;

class ClientHandler : public IEventHandler
{
public:
    explicit ClientHandler(TaskManager* taskManager);
    ~ClientHandler() override;




    void HandleRead(SOCKET socket, ISocket* reactor) override;
    void HandleWrite(SOCKET socket, ISocket* reactor) override;
    void HandleError(SOCKET socket, ISocket* reactor) override;
    bool HasDataToSend() override;
    bool HasDataToParse() override;


    void AddDataToSend(std::string data);
    std::string GetDataToSend();
    std::string GetDataToParse();

    void SetBufferSizes(int readSize, int writeSize);

private:
    int m_sessionId = 0;
    int m_requestsCount = 0;
    int m_responsesCount = 0;
    std::chrono::time_point<std::chrono::steady_clock> m_startTime;


    std::array<char, DEFAULT_BUFFER_SIZE> m_readBuffer = {};
    std::array<char, DEFAULT_BUFFER_SIZE> m_writeBuffer = {};

    std::queue<std::string> m_receivedData;
    std::queue<std::string> m_dataToSend;

    TaskManager* m_taskManager;

};


#endif //CLIENTHANDLER_H
