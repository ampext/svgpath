#svgpath 
##C++ library for rendering SVG paths and glyphs 
[![Build Status](https://travis-ci.org/ampext/svgpath.svg?branch=master)](https://travis-ci.org/ampext/svgpath)

The library provides wxWidgets controls and methods for rendering svg path data and svg fonts (WebFonts sush as "Font Awesome"). Supports wxGraphicsContext, Cairo and Direct2D backends. Temporary arcTo path element not implemented.
The library also provided wxWidgets control and path viewer application based on this widget.

![svgpathviewer](https://github.com/ampext/ampext.github.io/blob/master/images/svgpathviewer.png)
![svgglyphviwer](https://github.com/ampext/ampext.github.io/blob/master/images/svgglyphviewer.png)

##Dependencies
* wxWidgets (viewers and controls)
* Catch (tests) - optional
* Cairo (cairo rendering backend) - optional

##Usage
Creating control for showing svg font glyph:
```cpp
#include <svgglyphctrl.h>
#include <svgfont.h>

// somewhere in UI-related code
SvgFont font(L"font.svg");
SvgGlyphCtrl *glyphCtrl = new SvgGlyphCtrl(parent, wxID_ANY, font.GetGlyph(0xf000),
    fontSize, wxALIGN_CENTER);
```
Generating wxBitmap from svg font glyph:
```cpp
#include <wxcontext.h>
#include <svgfont.h>

SvgFont font(L"font.svg");
wxBitmap bitmap = GetBitmapForGlyph(font.GetGlyph(0xf020), fontSize, fontColor, bgColor);
```

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
`-DTESTS=1/0` for enable or disable tests from build. Execute `wget -P tests https://raw.githubusercontent.com/philsquared/Catch/3b18d9e962835100d7e12ac80d22882e408e40dc/single_include/catch.hpp` in source root directory for fetching dependency (Catch 1.2.1)

`-DVIEWERS=1/0` for enable or disable viewers from build

`-DSAMPLES=1/0` for enable or disable samples from build
