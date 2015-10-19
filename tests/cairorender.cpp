#include "renderdata.h"

#include <svgpath.h>
#include <cairocontext.h>

#include <vector>
#include <cairo/cairo.h>

int main()
{  
	cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1000, 1000);
	cairo_t *g = cairo_create(surface);

	cairo_set_source_rgb(g, 0.75, 0.34, 0.0);

	CairoContext graphicsContext(g);
	draw(&graphicsContext, testData01);
	graphicsContext.stroke();

	cairo_surface_write_to_png(surface, "cairotest.png");
	
	cairo_surface_destroy(surface);
	cairo_destroy(g);  
	
	
	return 0;
}
