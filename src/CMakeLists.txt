project(svgpath)
cmake_minimum_required(VERSION 3.0)

include_directories(${CAIRO_INCLUDE})

if(NOT CAIRO_LIB)
	set(CAIRO_LIB "cairo")
endif()

find_package(wxWidgets COMPONENTS xrc html adv core xml base REQUIRED)
include("${wxWidgets_USE_FILE}")

add_library(svgpath svgpath.cpp cairocontext.cpp svgpathctrl.cpp)
target_link_libraries(svgpath ${CAIRO_LIB})

add_executable(svgpathviewer svgpathdialog.cpp svgpathviewer.cpp)
target_link_libraries(svgpathviewer svgpath ${wxWidgets_LIBRARIES})