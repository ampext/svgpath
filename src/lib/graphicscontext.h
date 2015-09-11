#pragma once

class SVGPATHAPI GraphicsContext
{
public:
	virtual void moveTo(double x, double y) = 0;
	virtual void lineTo(double x, double y) = 0;
	virtual void curveTo(double x1, double y1, double x2, double y2, double x3, double y3) = 0;
	virtual void closePath() = 0;
	virtual void getCurrentPoint(double &x, double &y) = 0;
	virtual void getBoundingRect(double &x, double &y, double &w, double &h) = 0;

	virtual void stroke() = 0;
	virtual void fill() = 0;
};