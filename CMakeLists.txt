cmake_minimum_required(VERSION 3.17)
project(rogue)

set(CMAKE_CXX_STANDARD 20)

add_executable(rogue main.cpp src/state.h src/render.cpp src/render.h src/input.cpp src/input.h)
