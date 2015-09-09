cmake_minimum_required(VERSION 3.0)
project(sdl2web)

add_executable(sdl2web main.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})
set_property(TARGET sdl2web PROPERTY CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if (EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set_target_properties(sdl2web PROPERTIES LINK_FLAGS "-s USE_SDL=2")
else ()
  if (WIN32)
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(sdl2web ${GLEW_LIBRARIES})
  else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic -Wextra")
  endif()

  find_package(SDL2 REQUIRED)
  include_directories(${SDL2_INCLUDE_DIRS})
  target_link_libraries(sdl2web ${SDL2_LIBRARIES})
  find_package(OpenGL REQUIRED)
  target_link_libraries(sdl2web ${OPENGL_LIBRARIES})
endif()

