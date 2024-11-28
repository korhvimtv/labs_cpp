cmake_minimum_required(VERSION 3.29)
project(lab_work)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/sqlite)

add_library(sqlite3 STATIC
        ${CMAKE_SOURCE_DIR}/sqlite/sqlite3.c
)

add_executable(lab_work main.cpp
        user/user.cpp
        user/user.h
        libs.h
        func/func.cpp
        func/func.h
        dbFunc/dbsqlite.cpp
        dbFunc/dbsqlite.h
        user/infoProvider.h
        lab_4/pol.cpp
        lab_4/pol.h
        lab_5/templates.cpp
        lab_5/templates.h
        lab_6/exeptions.h
        lab_7/uploadToJSON.cpp
        lab_7/uploadToJSON.h
)

target_link_libraries(lab_work PRIVATE sqlite3)

target_include_directories(lab_work PRIVATE ${CMAKE_SOURCE_DIR}/sqlite)