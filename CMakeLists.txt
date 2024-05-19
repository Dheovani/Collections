cmake_minimum_required(VERSION 3.12)
project(Collections)

set(CMAKE_CXX_STANDARD 20)
set(SOURCES main.cpp)

add_executable(Collections ${SOURCES} "List.h")
