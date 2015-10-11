project(samples)

include_directories("../src/lib")

file(DOWNLOAD "https://raw.githubusercontent.com/github/octicons/v3.1.0/octicons/octicons.svg" "samples/octicons.svg" SHOW_PROGRESS)

add_executable(repoapp repodialog.cpp repoapp.cpp listviewrenderer.cpp)
target_link_libraries(repoapp svgpath)