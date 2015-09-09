#svgpath
##C++ library for rendering SVG paths and glyphs

This is library for rendering svg path data. Supports wxGraphicsContext and Cairo backends. Temporary arcTo path element not implemented.
The library also provided wxWidgets control and path viewer application based on this widget.

![svgpathviewer](https://github.com/ampext/ampext.github.io/blob/master/images/svgpathviewer.png)

##Building
###Breif
    mkdir build
    cd build
    cmake ..
    make
####CMake Options
`-DTESTS=1/0` for enable or disablie tests from build

`-DVIEWERS=1/0` for enable or disablie viewers from build
