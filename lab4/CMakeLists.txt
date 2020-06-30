cmake_minimum_required(VERSION 3.15)
project(lab4)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES main.cpp)


add_executable(lab4 ${SOURCES})

add_subdirectory(strategies)
add_subdirectory(game)

target_link_libraries(lab4 strategies game)
