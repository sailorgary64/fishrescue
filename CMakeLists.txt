cmake_minimum_required(VERSION 2.4)
PROJECT(graphics_coursework)

SET (CMAKE_BUILD_TYPE DEBUG)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/includes)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
include(FindOpenGL)
include(FindGLUT)
# module linker flags
#SET (CMAKE_MODULE_LINKER_FLAGS ${CMAKE_MODULE_LINKER_FLAGS_INIT} $ENV{LDFLAGS} "-l glut")

SET(INCLUDE_FILES
	includes/includes.hpp
	includes/game.hpp
	includes/input.hpp
	includes/actor.hpp
	includes/player.hpp
	includes/level.hpp
	includes/fps.hpp
	includes/enemy.hpp
	includes/cell.hpp
)

SET(CODE_FILES
	src/main.cpp
	src/game.cpp
	src/input.cpp
	src/player.cpp
	src/level.cpp
	src/fps.cpp
	src/enemy.cpp
	src/cell.cpp
)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	if(NOT DEFINED MINGW)
		SET(CODE_FILES ${CODE_FILES} ${INCLUDE_FILES})
	endif(NOT DEFINED MINGW)
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")
#if(GLUT_FOUND)
	add_executable (fish ${CODE_FILES})
#endif(GLUT_FOUND)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	if(DEFINED MINGW)
		SET(CMAKE_EXE_LINKER_FLAGS "-mwindows -fopenmp")
	else(DEFINED MINGW)
		SET(CMAKE_CXX_FLAGS "/DGLUT_BUILDING_LIB /openmp")
		SET(CMAKE_EXE_LINKER_FLAGS "/subsystem:windows /entry:mainCRTStartup")
	endif(DEFINED MINGW)
	target_link_libraries (fish opengl32 glu32 glut32)
else(CMAKE_SYSTEM_NAME MATCHES "Windows")
	SET(CMAKE_EXE_LINKER_FLAGS "-fopenmp")
	target_link_libraries (fish glut)
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")

