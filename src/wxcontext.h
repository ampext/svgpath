#pragma once

#include "graphicscontext.h"
#include <wx/graphics.h>

class wxGraphicsContext;

class wxContext: public GraphicsContext
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