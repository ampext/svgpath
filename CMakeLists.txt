cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0043)
	cmake_policy(SET CMP0043 OLD)
endif()

option(TESTS "build tests" ON)
option(VIEWERS "build viewers" ON)
option(SAMPLES "build samples" ON)

if(NOT CAIRO_LIB OR NOT CAIRO_INCLUDE)
	set(USE_CAIRO_FLAG 0)
else()
	include_directories(${CAIRO_INCLUDE})
	set(USE_CAIRO_FLAG 1)
endif()


find_package(wxWidgets COMPONENTS xrc html adv core xml base REQUIRED)
include("${wxWidgets_USE_FILE}")

if(${CMAKE_COMPILER_IS_GNUCXX})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -Wall")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4514 /wd4251 /wd4275")
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_subdirectory(src/lib)

if(${VIEWERS})
    add_subdirectory(src/viewers)
endif()

if(${SAMPLES})
	add_subdirectory(samples)
endif()

if(${TESTS})
	add_subdirectory(tests)
endif()