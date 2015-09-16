project(svgviewers)
cmake_minimum_required(VERSION 2.8)

include_directories("../lib")

add_executable(svgpathviewer WIN32 svgpathdialog.cpp svgpathviewer.cpp)
target_link_libraries(svgpathviewer svgpath)

add_executable(svgglyphviewer WIN32 svgglyphdialog.cpp svgglyphviewer.cpp glyphcellrenderer.cpp)
target_link_libraries(svgglyphviewer svgpath)