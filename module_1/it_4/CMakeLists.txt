cmake_minimum_required(VERSION 3.8)

project(it_4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Werror")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(it_4
    source/main.cpp
)

