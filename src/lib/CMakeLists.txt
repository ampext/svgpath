project(svgpath)

add_library(svgpath STATIC svgpath.cpp cairocontext.cpp wxcontext.cpp svgpathctrl.cpp svgglyphctrl.cpp svgpathctrlbase.cpp svgfont.cpp measurecontext.cpp)
target_link_libraries(svgpath ${CAIRO_LIB} ${wxWidgets_LIBRARIES})