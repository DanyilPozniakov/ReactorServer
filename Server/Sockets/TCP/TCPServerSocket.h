//
// Created by pozni on 3/9/2025.
//

#ifndef TCPSERVERSOCKET_H
#define TCPSERVERSOCKET_H

#include <Winsock2.h>

#include <atomic>
#include <array>
#include <utility>
#include <map>
#include <vector>
#include <memory>

#include <IEventHandler.h>
#include <ServerHandler.h>
#include <ISocket.h>
#include <unordered_map>
#include <unordered_set>

#include "ISocket.h"

// class TaskManager;
class IEventHandler;
class WordsServer;


class Connection
{
public:
    Connection(SOCKET socket, IEventHandler* handler, TaskManager* taskManager);
    virtual ~Connection();


    SOCKET m_socket;
    std::unique_ptr<IEventHandler> m_handler;
    std::string m_clientName;
};


class TCPServerSocket : public ISocket
{
public:
    explicit TCPServerSocket(const std::string& ip, const std::string& port, WordsServer* server);
    ~TCPServerSocket() override;

    bool Initialize() override;
    void Close() override;

    void SetTimeout(int milliseconds) const;
    void RegisterHandler(SOCKET socket, IEventHandler* handler) override;
    void RemoveHandler(SOCKET socket) override;


    [[nodiscard]] bool IsOpen() const;


    void eventLoop();
    std::atomic<bool> m_isRunning = false;

private:
    std::pair<SOCKET, std::unique_ptr<ServerHandler>> m_listener;
    std::map<SOCKET,IEventHandler*> m_clientSockets; // maybe change to std::unordered_map

    WordsServer* m_server;

};


#endif //TCPSERVERSOCKET_H
