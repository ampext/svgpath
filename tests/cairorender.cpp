#include "../src/svgpath.h"
#include "../src/cairocontext.h"

#include <iostream>
#include <vector>
#include <cairo/cairo.h>

std::vector<std::string> testData01 = 
{
	"M100,200 C100,100 400,100 400,200",
	"M100,500 C25,400 475,400 400,500",
	"M100,800 C175,700 325,700 400,800",
	"M600,200 C675,100 975,100 900,200",
	"M600,500 C600,350 900,650 900,500",
	"M600,800 C625,700 725,700 750,800 S875,900 900,800"
};

void render(GraphicsContext *g, const std::string path)
{
    SvgPath svgPath(path);
    svgPath.render(g);
}

void render(GraphicsContext *g, const std::vector<std::string> paths)
{
	for (const std::string &path: paths)
	{
		SvgPath svgPath(path);
        
        if (svgPath.isOk())
            svgPath.render(g);
	}
}

int main()
{  
	cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1000, 1000);
	cairo_t *g = cairo_create(surface);

	cairo_set_source_rgb(g, 0.75, 0.34, 0.0);

	CairoContext graphicsContext(g);
	render(&graphicsContext,testData01);

	cairo_stroke(g);
	//cairo_fill(g);

	cairo_surface_write_to_png(surface, "cairotest.png");
	
	cairo_surface_destroy(surface);
    cairo_destroy(g);  
	
    
    return 0;
}
