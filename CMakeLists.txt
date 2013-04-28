project(glft)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${glft_SOURCE_DIR}/cmake")

if (UNIX)
	add_definitions(-Wall -g -DUNIX -DGLFT_EXPORT=)
else (UNIX)
	add_definitions(-D_USE_MATH_DEFINES)
endif (UNIX)

find_package(OpenGL REQUIRED)
find_package(FreeType REQUIRED)

include_directories(. ${FREETYPE_INCLUDE_DIRS})

cmake_policy(SET CMP0003 NEW)

set (SOURCES atlas binpacker font)

set (LIBRARIES  ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${FREETYPE_LIBRARY})

if (UNIX)
	set_source_files_properties(${SOURCES} PROPERTIES COMPILE_FLAGS "-std=c++0x")
	add_library(glft SHARED ${SOURCES})
else (UNIX)
	add_library(glft SHARED ${SOURCES})
	set_property(TARGET glft
	             APPEND_STRING
		     PROPERTY COMPILE_DEFINITIONS "GLFT_EXPORT=__declspec(dllexport)")
endif(UNIX)

target_link_libraries(glft ${LIBRARIES})
