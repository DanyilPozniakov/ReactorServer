//
// Created by pozni on 3/15/2025.
//

#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H


#include <winsock2.h>

#include "ISocket.h"
#include "IEventHandler.h"


class TaskManager;

class Reactor;

class ServerHandler : public IEventHandler
{
public:
    explicit ServerHandler(TaskManager* reactor);
    ~ServerHandler() override;


    void HandleAccept(SOCKET socket, ISocket* reactor);
    void HandleDisconnect(SOCKET socket, ISocket* reactor);

    void HandleRead(SOCKET socket, ISocket* reactor) override;
    void HandleWrite(SOCKET socket, ISocket* reactor) override;
    void HandleError(SOCKET socket, ISocket* reactor) override;
    bool HasDataToParse()   override;
    bool HasDataToSend() override;

private:
    TaskManager* m_taskManager;
};


#endif //SERVERHANDLER_H
