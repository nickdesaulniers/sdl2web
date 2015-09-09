# Modified from:
# https://raw.githubusercontent.com/mertcanekiz/Muhittin/master/cmake/FindSDL2.cmake
# C:\Program Files\SDL2
#                      \SDL2.lib # 64 bit version from SDL2-devel-2.0.3-VC.zip
#                      \include

SET(SDL2_SEARCH_PATHS
  $ENV{ProgramW6432}/SDL2
  # TODO: Fix for OSX
)


FIND_PATH(SDL2_INCLUDE_DIRS SDL.h
  PATHS ${SDL2_SEARCH_PATHS}
  PATH_SUFFIXES include/SDL2 include
  DOC "The directory where SDL.h resides"
)

FIND_LIBRARY(SDL2_LIBRARIES
  NAMES SDL2 SDL2main
  PATHS ${SDL2_SEARCH_PATHS}
  PATH_SUFFIXES lib lib64 lib/x86 lib/x64
  DOC "The SDL2 library"
)

IF (SDL2_INCLUDE_DIRS AND SDL2_LIBRARIES)
  SET(SDL2_FOUND TRUE)
  MESSAGE(STATUS "Looking for SDL2 - found")
ELSE ()
  SET(SDL2_FOUND FALSE)
  MESSAGE(STATUS "Looking for SDL2 - not found")
ENDIF ()