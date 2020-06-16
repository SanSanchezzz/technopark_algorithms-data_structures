cmake_minimum_required(VERSION 3.8)

project(it_1)

#set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall")
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(INC
   include/i_graph.hpp
   include/arc_graph.hpp
   include/list_graph.hpp
   include/matrix_graph.hpp
   include/set_graph.hpp
)

set(SRC
    source/arc_graph.cpp
    source/list_graph.cpp
    source/matrix_graph.cpp
    source/set_graph.cpp
)

add_executable(it_1
    ${INC}
    source/main.cpp
    ${SRC}
)

target_include_directories(it_1
    PUBLIC
        "include"
)
