cmake_minimum_required(VERSION 3.30)
project(example)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE INSERT_LIBRARY_NAME)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
