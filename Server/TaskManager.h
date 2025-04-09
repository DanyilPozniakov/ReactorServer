//
// Created by pozni on 3/23/2025.
//

#ifndef TASKMANAGER_H
#define TASKMANAGER_H


#include <unordered_set>
#include <queue>
#include "TCPServerSocket.h"

class ClientHandler;

struct Task
{
    ClientHandler* handler;
    std::string data;
};



class TaskManager
{
public:
    TaskManager();
    virtual ~TaskManager();


    void AddConnection(ClientHandler* connection);

    bool CheckConnections();

private:
    std::vector<ClientHandler*> m_connections;

    std::queue<Task> taskQueueInProgress;
    std::queue<Task> taskQueueReady;
};


#endif //TASKMANAGER_H
