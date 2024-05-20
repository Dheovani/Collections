cmake_minimum_required(VERSION 3.12)
project(Collections)

set(CMAKE_CXX_STANDARD 20)
set(SOURCES src/main.cpp)

aux_source_directory(src SRC)

add_executable(Collections ${SOURCES} ${SRC})
