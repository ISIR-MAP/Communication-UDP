cmake_minimum_required(VERSION 2.8.3)
project(socket)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

#set(VIRTUOSE_INCLUDE_DIRS include)

#include_directories("${VIRTUOSE_INCLUDE_DIRS}")

add_executable(server server.cpp)
add_executable(client client.cpp)
