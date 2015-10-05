#pragma once

#include "graphicscontext.h"

class SVGPATHAPI MeasureContext: public GraphicsContext
{
public:
	MeasureContext();

	void moveTo(double x, double y) override;
	void lineTo(double x, double y) override;
	void curveTo(double x1, double y1, double x2, double y2, double x3, double y3) override;
	void closePath() override;
	void getCurrentPoint(double &x, double &y) override;
	void getBoundingRect(double &x, double &y, double &w, double &h) override;

	void stroke() {}
	void fill() {}

	void clear();

private:
	void updateMinMax(double x, double y);

private:
	double x;
	double y;

	double xMin;
	double xMax;
	double yMin;
	double yMax;
};