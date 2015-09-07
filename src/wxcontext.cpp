#include "wxcontext.h"
#include <wx/graphics.h>

wxContext::wxContext(wxGraphicsContext *g)
{
	this->g = g;
	path = g->CreatePath();
}

void wxContext::moveTo(double x, double y)
{
	path.MoveToPoint(x, y);
}

void wxContext::lineTo(double x, double y)
{
	path.AddLineToPoint(x, y);
}

void wxContext::curveTo(double x1, double y1, double x2, double y2, double x3, double y3)
{
	path.AddCurveToPoint(x1, y1, x2, y2, x3, y3);
}

void wxContext::closePath()
{
	path.CloseSubpath();
}

void wxContext::getCurrentPoint(double &x, double &y)
{
	path.GetCurrentPoint(&x, &y);
}

void wxContext::getBoundingRect(double &x, double &y, double &w, double &h) 
{
	path.GetBox(&x, &y, &w, &h);
}

void wxContext::stroke()
{
	g->StrokePath(path);
}

void wxContext::fill()
{
	g->FillPath(path, wxWINDING_RULE);
}