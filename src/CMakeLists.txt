project(svgpath)
cmake_minimum_required(VERSION 3.0)

include_directories(${CAIRO_INCLUDE})

if(NOT CAIRO_LIB)
	set(CAIRO_LIB "cairo")
endif()

add_library(svgpath svgpath.cpp cairocontext.cpp)
target_link_libraries(svgpath ${CAIRO_LIB})