//
// Created by pozni on 3/15/2025.
//

#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H

#include <complex.h>

#include "Winsock2.h"

class ISocket;

class Connection;

class IEventHandler {
public:
    virtual ~IEventHandler() = default;


    virtual void HandleRead(SOCKET socket, ISocket* reactor)        = 0;
    virtual void HandleWrite(SOCKET socket, ISocket* reactor)       = 0;
    virtual void HandleError(SOCKET socket, ISocket* reactor)       = 0;
    virtual bool HasDataToSend()                                    = 0;
    virtual bool HasDataToParse()                                   = 0;


    uint32_t m_sessionId = 0;
    SOCKET m_socket = INVALID_SOCKET;

};



#endif //IEVENTHANDLER_H
