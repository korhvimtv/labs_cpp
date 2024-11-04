cmake_minimum_required(VERSION 3.29)
project(lab_2)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/sqlite)

add_library(sqlite3 STATIC
        ${CMAKE_SOURCE_DIR}/sqlite/sqlite3.c
)

add_executable(lab_2 main.cpp
        user/user.cpp
        user/user.h
        libs.h
        func/func.cpp
        func/func.h
        dbFunc/dbsqlite.cpp
        dbFunc/dbsqlite.h
)

target_link_libraries(lab_2 PRIVATE sqlite3)

target_include_directories(lab_2 PRIVATE ${CMAKE_SOURCE_DIR}/sqlite)