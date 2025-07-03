cmake_minimum_required(VERSION 3.30)
project(INSERT_LIBRARY_NAME LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
        src/INSERT_LIBRARY_NAME.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_subdirectory(example)