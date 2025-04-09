add_library(Server STATIC
        WordsServer.cpp
        WordsServer.h
        ThreadPool.cpp
        ThreadPool.h
        TaskManager.cpp
        TaskManager.h
        Parser/IProtocolParser.h

)

target_include_directories(Server PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Sockets
)



target_link_libraries(Server PUBLIC
        Qt6::Core
        Qt6::Network
        Sockets
)
