cmake_minimum_required(VERSION 3.16)
project(OSex4 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
add_executable(OSex4 test.c threadPool.c osqueue.c)