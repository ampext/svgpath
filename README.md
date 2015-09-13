#svgpath
##C++ library for rendering SVG paths and glyphs

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
If you have a custom wxWidgets build pass `-DwxWidgets_CONFIG_EXECUTABLE=<oath to wx-config>`
###Windows (Visual Studio)
    mkdir build
    cd build
    cmake -G "NMake Makefiles" -DwxWidgets_ROOT_DIR=<path to wxWidgets> ..
    nmake
####CMake Options
`-DTESTS=1/0` for enable or disable tests from build

`-DVIEWERS=1/0` for enable or disable viewers from build
