#include "wxcontext.h"
#include "svgglyph.h"
#include "svgpath.h"

#include <wx/dcmemory.h>

#include <memory>

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

wxBitmap GetBitmapForGlyph(const SvgGlyph &glyph, int size, const wxColor &color)
{
	if (!glyph.isOk())
		return wxNullBitmap;

	SvgPath path(glyph.data.ToStdString());

	if (!path.isOk())
		return wxNullBitmap;

    int width = glyph.getWidth(size);
	int height = glyph.getHeight(size);
	double scale = static_cast<double>(width) / (glyph.horizAdvX > 0 ? glyph.horizAdvX : glyph.unitsPerEm);

	wxBitmap bitmap(width, height, 32);
	wxMemoryDC memoryDC;

	memoryDC.SelectObject(bitmap);
	memoryDC.SetBackgroundMode(wxPENSTYLE_TRANSPARENT);
	memoryDC.Clear();

    std::unique_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(memoryDC));
	gc->SetBrush(wxBrush(color));

	wxContext pathContext(gc.get());

    gc->PushState();
    gc->Translate(0, height + glyph.getVerticalOffset(size));
	gc->Scale(scale, -scale);

	path.render(&pathContext);

	pathContext.fill();
	gc->PopState();

	gc.reset();
	memoryDC.SelectObject(wxNullBitmap);

	return bitmap;
}