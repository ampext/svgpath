cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0043)
	cmake_policy(SET CMP0043 OLD)
endif()

option(TESTS "build tests" ON)
option(VIEWERS "build viewers" ON)
option(SAMPLES "build samples" ON)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

include_directories(${CAIRO_INCLUDE})

if(NOT CAIRO_LIB)
	set(CAIRO_LIB "cairo")
endif()

find_package(wxWidgets COMPONENTS xrc html adv core xml base REQUIRED)
include("${wxWidgets_USE_FILE}")

if(${CMAKE_COMPILER_IS_GNUCXX})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -Wall")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4514 /wd4251 /wd4275")
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