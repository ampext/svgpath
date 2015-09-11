project(tests)
cmake_minimum_required(VERSION 3.0)

include_directories(${CATCH_INCLUDE} "../src/lib")

add_executable(tests main.cpp pathreader.cpp fontloader.cpp)
target_link_libraries(tests svgpath)

add_executable(cairorender cairorender.cpp)
target_link_libraries(cairorender svgpath)