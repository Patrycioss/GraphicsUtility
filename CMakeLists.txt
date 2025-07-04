cmake_minimum_required(VERSION 3.30)
project(graphics_utility LANGUAGES CXX)
include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG 877399b #3.2.10
)

FetchContent_MakeAvailable(SDL3)

add_library(${PROJECT_NAME} STATIC
        src/sdl3/triangle/sdl3_triangle.cpp
        src/graphics_utility.cpp
        src/sdl3/sdl3_graphics_utility.cpp
        src/sdl3/sdl3_utility.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC SDL3::SDL3)

add_subdirectory(example)