//
// Created by pozni on 3/2/2025.
//


#include <TCPServerSocket.h>

#include "WordsServer.h"

WordsServer::WordsServer()
{
}

WordsServer::~WordsServer()
{
    if (m_socketThread.joinable())
    {
        m_socketThread.join();
    }
    delete m_taskManager;
}



void WordsServer::Init()
{
    m_taskManager = new TaskManager();
}

void WordsServer::Run()
{
    //TODO: add exit command...
     m_socketThread = std::thread([&]()
    {
        TCPServerSocket server("localhost", "3434",this);
        server.Initialize();
        server.m_isRunning = true;
        server.eventLoop();
    });

    while (true)
    {
       if(!m_taskManager->CheckConnections())
       {
           std::this_thread::sleep_for(std::chrono::milliseconds(100));
       }
    }
}

void WordsServer::Shutdown()
{
}

TaskManager* WordsServer::GetTaskManager() const
{
    return m_taskManager;
}


