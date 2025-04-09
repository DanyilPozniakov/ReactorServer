//
// Created by pozni on 3/2/2025.
//

#include <iostream>
#include <WordsServer.h>


#include "Sockets/TCP/TCPServerSocket.h"




int main(int argc, char* argv[])
{
    std::string host = argc > 1 ? argv[1] : "localhost";
    std::string port = argc > 2 ? argv[2] : "3434";

    WordsServer server;
    server.Init();
    server.Run();

    return 0;
}
