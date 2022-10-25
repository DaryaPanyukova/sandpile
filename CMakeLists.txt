cmake_minimum_required(VERSION 3.21)
project(labwork_3_DaryaPanyukova)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(labwork_3_DaryaPanyukova
        Color.h
        Image.cpp
        Image.h
        main.cpp
        Sandpile.cpp
        Sandpile.h)
