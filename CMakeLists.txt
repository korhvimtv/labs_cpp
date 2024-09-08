cmake_minimum_required(VERSION 3.29)
project(lab_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab_1 main.cpp
        user/user.cpp
        user/user.h
        libs.h
        func/func.cpp
        func/func.h)
