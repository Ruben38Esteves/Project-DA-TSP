cmake_minimum_required(VERSION 3.16.3)
project(DAProject2)

set(CMAKE_CXX_STANDARD 20)

add_executable(DAProject2 main.cpp src/Manager.cpp src/Manager.h src/Graph.h src/VertexEdge.h src/VertexEdge.cpp src/Graph.cpp src/MutablePriorityQueue.h)
