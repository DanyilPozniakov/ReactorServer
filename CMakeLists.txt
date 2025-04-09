
cmake_minimum_required(VERSION 3.0)
project(WordsServer)

set(PROJECT_VERSION 0.01)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/msvc2022_64")

find_package(Qt6 COMPONENTS Core Network REQUIRED)

include_directories(external/json/include)

add_subdirectory(Server)
add_subdirectory(Server/Sockets)
add_executable(WordsServer main.cpp)


target_link_libraries(WordsServer PUBLIC
        Qt6::Core
        Qt6::Network
        Server

)
