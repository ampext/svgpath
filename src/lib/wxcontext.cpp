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
	if (!glyph.IsOk())
		return wxNullBitmap;

	SvgPath path(glyph.data.ToStdString());

	if (!path.isOk())
		return wxNullBitmap;

	double x, y, w, h;
	{
		wxBitmap bitmap(1, 1);
		wxMemoryDC dc;
		dc.SelectObject(bitmap);

		std::unique_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(dc));

		wxContext pathContext(gc.get());

		path.render(&pathContext);
		pathContext.getBoundingRect(x, y, w, h);

		double k = static_cast<double>(size) / glyph.unitsPerEm;

		x *= k;
		y *= k;
		w *= k;
		h *= k;
	}

	double scale = static_cast<double>(glyph.GetWidth(size)) / (glyph.horizAdvX > 0 ? glyph.horizAdvX : glyph.unitsPerEm);

	int bitmapWidth = std::max<int>(std::round(w), glyph.GetWidth(size));
	int bitmapHeight = std::max<int>(std::round(h), glyph.GetHeight(size));

	wxBitmap bitmap(bitmapWidth, bitmapHeight, 32);
	wxMemoryDC memoryDC;

	memoryDC.SelectObject(bitmap);
	memoryDC.SetBackgroundMode(wxPENSTYLE_TRANSPARENT);
	memoryDC.Clear();

    std::unique_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(memoryDC));
	gc->SetBrush(wxBrush(color));

	wxContext pathContext(gc.get());

    gc->PushState();
    gc->Translate(0, bitmapHeight + y);
	gc->Scale(scale, -scale);

	path.render(&pathContext);

	pathContext.fill();
	gc->PopState();

	gc.reset();
	memoryDC.SelectObject(wxNullBitmap);

	return bitmap;
}