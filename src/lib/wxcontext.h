#pragma once

#include "defs.h"
#include "graphicscontext.h"

#include <wx/graphics.h>
#include <wx/bitmap.h>

struct SvgGlyph;

class SVGPATHAPI wxContext: public GraphicsContext
{
public:
	wxContext(wxGraphicsContext *g);

	void moveTo(double x, double y) override;
	void lineTo(double x, double y) override;
	void curveTo(double x1, double y1, double x2, double y2, double x3, double y3) override;
	void closePath() override;
	void getCurrentPoint(double &x, double &y) override;
	void getBoundingRect(double &x, double &y, double &w, double &h) override;

	void stroke() override;
	void fill() override;

private:
	wxGraphicsContext *g;
	wxGraphicsPath path;
};

SVGPATHAPI wxBitmap GetBitmapForGlyph(const SvgGlyph &glyph, int size, const wxColor &color = *wxBLACK);