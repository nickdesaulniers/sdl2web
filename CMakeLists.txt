cmake_minimum_required(VERSION 3.0)
add_executable(main main.cpp)
add_definitions(-Wall -Wextra -O3)

if (NOT EMSCRIPTEN)
  set(SDL2_DIR "./")
  find_package(SDL2 REQUIRED)
  include_directories(${SDL2_INCLUDE_DIR})
  target_link_libraries(main ${SDL2_LIBRARY})
  add_definitions(-std=c++14)

  find_package(OpenGL REQUIRED)
  target_link_libraries(main ${OPENGL_LIBRARIES})
endif()

if (EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  add_definitions(-s USE_SDL=2 -std=c++1y)
endif()

