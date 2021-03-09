cmake_minimum_required(VERSION 3.17)
project(rogue)

set(CMAKE_CXX_STANDARD 20)

add_executable(rogue
        src/main.cpp src/state.h src/render.cpp src/render.h src/input.cpp src/input.h src/save.cpp src/save.h
        src/generate.cpp src/generate.h
        )

link_directories(C:\\Program Files \(x86\)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x64)
target_link_libraries(rogue WinMM.Lib)
