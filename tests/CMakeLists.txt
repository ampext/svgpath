project(tests)

include_directories(${CATCH_INCLUDE} "../src/lib")

configure_file(font0.svg font0.svg COPYONLY)
configure_file(font1.svg font1.svg COPYONLY)
configure_file(font2.svg font2.svg COPYONLY)

add_executable(tests main.cpp pathreader.cpp fontloader.cpp path.cpp)
target_link_libraries(tests svgpath)

if(CAIRO_RENDERER)
	add_executable(cairorender cairorender.cpp)
	target_link_libraries(cairorender svgpath)
endif()

if(D2D_RENDERER)
	add_executable(d2drender d2drender.cpp)
	target_link_libraries(d2drender svgpath)
endif()