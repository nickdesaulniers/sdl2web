cmake_minimum_required(VERSION 3.0)
add_executable(main main.cpp)
add_definitions(-Wall -Wextra -O3 -std=c++14)

set(SDL2_DIR "./")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(main ${SDL2_LIBRARY})

