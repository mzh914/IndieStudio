cmake_minimum_required(VERSION 3.17)

if(CMAKE_SYSTEM MATCHES Windows)
    set(CMAKE_CXX_COMPILER "C:/Program Files/mingw64/bin/g++.exe" )
    set(CMAKE_C_COMPILER "C:/Program Files/mingw64/bin/gcc.exe" )
    set(CMAKE_CXX_FLAGS "-std=c++20")
endif()

project(indie_studio)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(BINARY_NAME bomberman)
set(CXX 20)

FIND_PACKAGE(raylib REQUIRED)

ADD_SUBDIRECTORY(src)