#include "measurecontext.h"
#include "svgutils.h"

#include <cmath>

MeasureContext::MeasureContext()
{
	clear();
}

void MeasureContext::clear()
{
	x = 0;
	y = 0;

	startX = std::numeric_limits<double>::quiet_NaN();
	startY = std::numeric_limits<double>::quiet_NaN();

	xMin = std::numeric_limits<double>::max();
	xMax = std::numeric_limits<double>::lowest();
	yMin = std::numeric_limits<double>::max();
	yMax = std::numeric_limits<double>::lowest();
}

void MeasureContext::updateMinMax(double x, double y)
{
	xMin = std::min(xMin, x);
	xMax = std::max(xMax, x);
	yMin = std::min(yMin, y);
	yMax = std::max(yMax, y);
}

void MeasureContext::moveTo(double x, double y)
{
	this->x = x;
	this->y = y;

	if (std::isnan(startX)) startX = x;
	if (std::isnan(startY)) startY = y;

	updateMinMax(x, y);
}

void MeasureContext::lineTo(double x, double y)
{
	moveTo(x, y);
}

void MeasureContext::curveTo(double x1, double y1, double x2, double y2, double x3, double y3)
{
	double x, y, w, h;
	std::tie(x, y, w, h) = SvgUtils::getCurveBoundingRect(this->x, this->y, x1, y1, x2, y2, x3, y3);

	updateMinMax(x, y);
	updateMinMax(x + w, y + h);

	this->x = x3;
	this->y = y3;
}

void MeasureContext::closePath()
{
	lineTo(startX, startY);
}

void MeasureContext::getCurrentPoint(double &x, double &y)
{
	x = this->x;
	y = this->y;
}

void MeasureContext::getBoundingRect(double &x, double &y, double &w, double &h)
{
	if (xMin == std::numeric_limits<double>::max() ||
		yMin == std::numeric_limits<double>::max())
	{
		x = y = w = h = 0;
	}
	else
	{
		x = xMin;
		y = yMin;
		w = xMax - xMin;
		h = yMax - yMin;
	}
}