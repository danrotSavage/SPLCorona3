cmake_minimum_required(VERSION 3.17)
project(SPLcorona2)

set(CMAKE_CXX_STANDARD 11)

add_executable(SPLcorona2 src/main.cpp src/Graph.cpp )
add_executable(Tree src/main.cpp src/Graph.cpp src/Tree.cpp src/Session.cpp src/Agent.cpp)