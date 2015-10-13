#svgpath 
##C++ library for rendering SVG paths and glyphs 
[![Build Status](https://travis-ci.org/ampext/svgpath.svg?branch=master)](https://travis-ci.org/ampext/svgpath)

The library provides wxWidgets controls and methods for rendering svg path data and svg fonts (WebFonts sush as "Font Awesome"). Supports wxGraphicsContext and Cairo backends. Temporary arcTo path element not implemented.
The library also provided wxWidgets control and path viewer application based on this widget.

![svgpathviewer](https://github.com/ampext/ampext.github.io/blob/master/images/svgpathviewer.png)
![svgglyphviwer](https://github.com/ampext/ampext.github.io/blob/master/images/svgglyphviewer.png)

##Dependencies
* wxWidgets (viewers and controls)
* Catch (tests) - optional
* Cairo (cairo rendering backend) - optional

##Building
###Linux
    mkdir build
    cd build
    cmake ..
    make
If you have a custom wxWidgets build pass `-DwxWidgets_CONFIG_EXECUTABLE=<path to wx-config>`
###Windows (Visual Studio)
    mkdir build
    cd build
    cmake -G "NMake Makefiles" -DwxWidgets_ROOT_DIR=<path to wxWidgets> ..
    nmake
####CMake Options
`-DTESTS=1/0` for enable or disable tests from build. Execute `wget -P tests https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp` in source root directory for fetching dependency

`-DVIEWERS=1/0` for enable or disable viewers from build

`-DSAMPLES=1/0` for enable or disable samples from build
