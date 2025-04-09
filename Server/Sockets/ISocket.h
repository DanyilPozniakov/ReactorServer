//
// Created by pozni on 3/9/2025.
//

#ifndef ISOCKET_H
#define ISOCKET_H


#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <string>

class IEventHandler;

constexpr int DEFAULT_BUFFER_SIZE = 1024 * 10; // 10KB

class ISocket
{

public:
    virtual ~ISocket() = default;
    virtual bool Initialize() = 0;
    virtual void Close() = 0;
    virtual void RegisterHandler(SOCKET socket, IEventHandler* handler) = 0;
    virtual void RemoveHandler(SOCKET socket) = 0;


protected:
    SOCKET m_listenSocket = INVALID_SOCKET;
    static WSADATA wsaData;
    std::string port    = {};
    std::string ip      = {};

};

#endif //ISOCKET_H
