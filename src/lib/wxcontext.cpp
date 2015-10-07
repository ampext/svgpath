#include "wxcontext.h"
#include "measurecontext.h"
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
		MeasureContext measureContext;

		path.draw(&measureContext);
		measureContext.getBoundingRect(x, y, w, h);

		double k = static_cast<double>(size) / glyph.unitsPerEm;

		x *= k;
		y *= k;
		w *= k;
		h *= k;

		// one pixel border for AA
		x -= 1;
		y -= 1;
		w += 2;
		h += 2;
	}

	double scale = static_cast<double>(glyph.GetWidth(size)) / (glyph.horizAdvX > 0 ? glyph.horizAdvX : glyph.unitsPerEm);

	int bitmapWidth = std::max<int>(std::round(w), glyph.GetWidth(size));
	int bitmapHeight = std::max<int>(std::round(h), glyph.GetHeight(size));

	wxImage image(bitmapWidth, bitmapHeight, true);
	image.InitAlpha();

	std::unique_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(image));

	gc->SetCompositionMode(wxCOMPOSITION_SOURCE);
	gc->SetBrush(wxBrush(wxColor(0, 0, 0, 0), wxBRUSHSTYLE_SOLID));
	gc->DrawRectangle(0, 0, bitmapWidth, bitmapHeight);
	gc->SetCompositionMode(wxCOMPOSITION_OVER);

	gc->SetBrush(wxBrush(color));

	wxContext pathContext(gc.get());

	gc->PushState();
	gc->Translate(0, bitmapHeight + y);
	gc->Scale(scale, -scale);

	path.draw(&pathContext);

	pathContext.fill();
	gc->PopState();

	gc.reset();

	return wxBitmap(image, 32);
}