
add_library(Sockets STATIC
        ISocket.h
        TCP/TCPServerSocket.cpp
        TCP/TCPServerSocket.h
        IEventHandler.h
        TCP/ServerHandler.cpp
        TCP/ServerHandler.h
        TCP/ClientHandler.cpp
        TCP/ClientHandler.h
)


target_include_directories(Sockets PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Sockets PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/TCP)

include_directories(Sockets PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(Sockets PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/TCP)
