project(svgpath)
cmake_minimum_required(VERSION 2.8)

add_library(svgpath STATIC svgpath.cpp cairocontext.cpp wxcontext.cpp svgpathctrl.cpp svgglyphctrl.cpp svgpathctrlbase.cpp svgfont.cpp)
target_link_libraries(svgpath ${CAIRO_LIB} ${wxWidgets_LIBRARIES})