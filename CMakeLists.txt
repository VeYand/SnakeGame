cmake_minimum_required(VERSION 3.26)
project(Anaconda)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

add_executable(Anaconda
        include/Anaconda.h
        include/ControlKeys.h
        include/Position.h
        include/SnakeGame.h
        src/Anaconda.cpp
        src/ControlKeys.cpp
        src/Position.cpp
        src/SnakeGame.cpp
        main.cpp
        include/GameMode.h
        include/GameMode.h
        src/GameMode.cpp
        include/GameParameter.h
        src/GameParameter.cpp
        src/GameParameter.cpp)

