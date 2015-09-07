#pragma once

#include "graphicscontext.h"

struct _cairo;
typedef struct _cairo cairo_t;

class CairoContext: public GraphicsContext
{
public:
	CairoContext(cairo_t *g);

	void moveTo(double x, double y) override;
	void lineTo(double x, double y) override;
	void curveTo(double x1, double y1, double x2, double y2, double x3, double y3) override;
	void closePath() override;
	void getCurrentPoint(double &x, double &y) override;

	void stroke() override;
	void fill() override;

private:
	cairo_t *g;
};