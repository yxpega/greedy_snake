cmake_minimum_required(VERSION 3.0)
project(greedy_snake)

add_definitions(-Wall -g)

set(PARTS_DIR ${PROJECT_SOURCE_DIR}/parts)

add_subdirectory(parts)
include_directories(${PARTS_DIR})

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} game_parts)
