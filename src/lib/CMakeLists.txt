project(svgpath)

set(SOURCES svgpath.cpp wxcontext.cpp svgpathctrl.cpp svgglyphctrl.cpp svgpathctrlbase.cpp svgfont.cpp measurecontext.cpp)
set(LIBRARIES ${wxWidgets_LIBRARIES})

if(USE_CAIRO_FLAG)
	set(SOURCES ${SOURCES} cairocontext.cpp)
	set(LIBRARIES ${LIBRARIES} ${CAIRO_LIB})
endif()

if(D2D_RENDERER)
	set(SOURCES ${SOURCES} d2dcontext.cpp)
endif()

add_library(svgpath STATIC ${SOURCES})
target_link_libraries(svgpath ${LIBRARIES})