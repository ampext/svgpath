project(svgpath)
cmake_minimum_required(VERSION 3.0)

find_package(wxWidgets COMPONENTS xrc html adv core xml base REQUIRED)
include("${wxWidgets_USE_FILE}")

add_library(svgpath svgpath.cpp cairocontext.cpp wxcontext.cpp svgpathctrl.cpp svgglyphctrl.cpp svgpathctrlbase.cpp)
target_link_libraries(svgpath ${CAIRO_LIB})

add_executable(svgpathviewer WIN32 svgpathdialog.cpp svgpathviewer.cpp)
target_link_libraries(svgpathviewer svgpath ${wxWidgets_LIBRARIES})

add_executable(svgglyphviewer WIN32 svgglyphdialog.cpp svgglyphviewer.cpp)
target_link_libraries(svgglyphviewer svgpath ${wxWidgets_LIBRARIES})