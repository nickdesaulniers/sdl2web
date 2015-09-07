cmake_minimum_required(VERSION 3.0)
project(sdl2web CXX)

add_executable(sdl2web main.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")

if (EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
  set_target_properties(sdl2web PROPERTIES LINK_FLAGS "-s USE_SDL=2")
else()
  set(SDL2_DIR "./")
  find_package(SDL2 REQUIRED)
  include_directories(${SDL2_INCLUDE_DIR})
  target_link_libraries(sdl2web ${SDL2_LIBRARY})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

  find_package(OpenGL REQUIRED)
  target_link_libraries(sdl2web ${OPENGL_LIBRARIES})
endif()

