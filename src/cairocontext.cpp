#include "cairocontext.h"
#include <cairo/cairo.h>

CairoContext::CairoContext(cairo_t *g)
{
	this->g = g;
}

void CairoContext::moveTo(double x, double y)
{
	cairo_move_to(g, x, y);
}

void CairoContext::lineTo(double x, double y)
{
	cairo_line_to(g, x, y);
}

void CairoContext::curveTo(double x1, double y1, double x2, double y2, double x3, double y3)
{
	cairo_curve_to(g, x1, y1, x2, y2, x3, y3);
}

void CairoContext::closePath()
{
	cairo_close_path(g);
}

void CairoContext::getCurrentPoint(double &x, double &y)
{
	cairo_get_current_point(g, &x, &y);
}

void CairoContext::getBoundingRect(double &x, double &y, double &w, double &h) 
{
	double left, top, right, bottom;
    cairo_path_extents(g, &left, &top, &right, &bottom);

    x = left;
    y = top;
    w = right - left;
    h = bottom - top;
}

void CairoContext::stroke()
{
	cairo_stroke(g);
}

void CairoContext::fill()
{
	cairo_fill(g);
}