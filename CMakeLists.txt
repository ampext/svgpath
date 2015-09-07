cmake_minimum_required(VERSION 3.0)

include_directories(${CAIRO_INCLUDE})

if(NOT CAIRO_LIB)
	set(CAIRO_LIB "cairo")
endif()

if(${CMAKE_COMPILER_IS_GNUCXX})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -Wall")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd 4514")
endif()

add_subdirectory(src)

if(${ENABLE_TESTS})
	add_subdirectory(tests)
endif()