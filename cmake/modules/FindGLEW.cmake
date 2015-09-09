# Modified from:
# https://raw.githubusercontent.com/robocomp/robocomp/6f0d6c6c5b3a0384f14d3e3b637f01cb2416cff9/cmake/modules/FindGLEW.cmake
# C:\Program Files\GLEW
#                      \glew32.lib # 64 bit version from glew-1.13.0.zip
#                      \glew32s.lib # 64 bit version from glew-1.13.0.zip
#                      \GL
#                         \glew.h
#                         \glxew.h
#                         \wglew.h
# Note: I had to manually build a x64 Release build of GLEW.

SET(GLEW_SEARCH_PATHS
  $ENV{ProgramW6432}/GLEW
)

FIND_PATH(GLEW_INCLUDE_DIRS GL/glew.h
  PATHS ${GLEW_SEARCH_PATHS}
  DOC "The directory where GL/glew.h resides"
)

FIND_LIBRARY(GLEW_LIBRARIES
  NAMES glew32 glew32s
  PATHS ${GLEW_SEARCH_PATHS}
  PATH_SUFFIXES lib
  DOC "The GLEW library"
)

IF (GLEW_INCLUDE_DIRS AND GLEW_LIBRARIES)
  SET(GLEW_FOUND TRUE)
  MESSAGE(STATUS "Looking for GLEW - found")
ELSE ()
  SET(GLEW_FOUND FALSE)
  MESSAGE(STATUS "Looking for GLEW - not found")
ENDIF ()