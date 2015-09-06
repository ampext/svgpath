#include "svgpath.h"
#include "svgutils.h"
#include "graphicscontext.h"

SvgPath::SvgPath(const std::string &str)
{
	setPath(str);
}

void SvgPath::setPath(const std::string &str)
{
	data.commands.clear();
	data.coords.clear();

	ok = true;
	lastError = "";

	if (str.empty())
	{
		ok = false;
		return;
	}

	pathString = str;

    auto it = str.begin();

    try
    {
		SvgUtils::readSvgPath(it, str.end(), std::back_inserter(data.commands), std::back_inserter(data.coords));
	}
	catch (std::exception &e)
	{
		lastError = e.what();
		ok = false;
	}
}

const std::string &SvgPath::getPath() const
{
	return pathString;
}

const SvgPath::PathData &SvgPath::getPathData() const
{
    return data;
}

bool SvgPath::isOk() const
{
    return ok;
}

std::string SvgPath::getLastError() const
{
	return lastError;
}

void SvgPath::render(GraphicsContext *g)
{
	if (!ok) return;

	std::vector<PathElement>::const_iterator commandIt = data.commands.begin();
	std::vector<double>::const_iterator coordsIt = data.coords.begin();

	PathElement prevCommand = PathElement::ClosePath;
	double x = 0, y = 0;
	double x1 = 0, y1 = 0;
	double x2 = 0, y2 = 0;
	double cx = 0, cy = 0;
	double prevX = 0, prevY = 0;
	double prevX1 = 0, prevY1 = 0;
	double prevX2 = 0, prevY2 = 0;

	while (commandIt != data.commands.end())
	{
		if (*commandIt == PathElement::MoveTo || 
			*commandIt == PathElement::LineTo ||
			*commandIt == PathElement::LineToRel)
		{
			x = *(coordsIt + 0);
			y = *(coordsIt + 1);

			std::advance(coordsIt, 2);	
		}
		else if (*commandIt == PathElement::LineToHorizontal || *commandIt == PathElement::LineToHorizontalRel)
		{
			x = *coordsIt;
			coordsIt++;
		}
		else if(*commandIt == PathElement::LineToVertical || *commandIt == PathElement::LineToVerticalRel)
		{
			y = *coordsIt;
			coordsIt++;
		}
		else if(*commandIt == PathElement::CurveToCubic || *commandIt == PathElement::CurveToCubicRel)
		{
			x1 = *(coordsIt + 0);
			y1 = *(coordsIt + 1);
			x2 = *(coordsIt + 2);
			y2 = *(coordsIt + 3);
			x = *(coordsIt + 4);
			y = *(coordsIt + 5);

			std::advance(coordsIt, 6);
		}
		else if(*commandIt == PathElement::CurveToCubicSmooth || *commandIt == PathElement::CurveToCubicSmoothRel)
		{
			x2 = *(coordsIt + 0);
			y2 = *(coordsIt + 1);
			x = *(coordsIt + 2);
			y = *(coordsIt + 3);

			std::advance(coordsIt, 4);
		}
		else if(*commandIt == PathElement::CurveToQuadratic || *commandIt == PathElement::CurveToQuadraticRel)
		{
			x1 = *(coordsIt + 0);
			y1 = *(coordsIt + 1);
			x = *(coordsIt + 2);
			y = *(coordsIt + 3);

			std::advance(coordsIt, 4);
		}
		else if(*commandIt == PathElement::CurveToQuadraticSmooth || *commandIt == PathElement::CurveToQuadraticSmoothRel)
		{
			x = *(coordsIt + 0);
			y = *(coordsIt + 1);

			std::advance(coordsIt, 2);
		}

		g->getCurrentPoint(cx, cy);

		if (*commandIt == PathElement::MoveTo)
		{
			g->moveTo(x, y);
		}
		else if (*commandIt == PathElement::LineTo || *commandIt == PathElement::LineToRel)
		{
			if (SvgUtils::isCommandRelative(*commandIt))
			{
				x += cx;
				y += cy;
			}

			g->lineTo(x, y);
		}
		else if (*commandIt == PathElement::LineToHorizontal || *commandIt == PathElement::LineToHorizontalRel)
		{
			if (SvgUtils::isCommandRelative(*commandIt))
				x += cx;

			g->lineTo(x, cy);
		}
		else if (*commandIt == PathElement::LineToVertical || *commandIt == PathElement::LineToVerticalRel)
		{
			if (SvgUtils::isCommandRelative(*commandIt))
				y += cy;

			g->lineTo(cx, y);
		}
		else if (*commandIt == PathElement::CurveToCubic || *commandIt == PathElement::CurveToCubicRel)
		{
			if (SvgUtils::isCommandRelative(*commandIt))
			{
				x += cx;
				y += cy;
				x1 += cx;
				y1 += cy;
				x2 += cx;
				y2 += cy;
			}

			g->curveTo(x1, y1, x2, y2, x, y);
		}
		else if (*commandIt == PathElement::CurveToCubicSmooth || *commandIt == PathElement::CurveToCubicSmoothRel)
		{
			if (SvgUtils::isCurveToCubic(prevCommand))
			{
				x1 = 2 * prevX - prevX2;
				y1 = 2 * prevY - prevY2;
			}
			else
			{
				x1 = cx;
				y1 = cy;
			}

			if (SvgUtils::isCommandRelative(*commandIt))
			{
				x += cx;
				y += cy;
				x2 += cx;
				y2 += cy;				
			}

			g->curveTo(x1, y1, x2, y2, x, y);
		}
		else if (*commandIt == PathElement::CurveToQuadratic || *commandIt == PathElement::CurveToQuadraticRel)
		{
			if (SvgUtils::isCommandRelative(*commandIt))
			{
				x += cx;
				y += cy;
				x1 += cx;
				y1 += cy;				
			}

			double qx1 = x1;
			double qy1 = y1;

			x1 = cx + 2.0 / 3.0 * (qx1 - cx);
			y1 = cy + 2.0 / 3.0 * (qy1 - cy);

			x2 = x + 2.0 / 3.0 * (qx1 - x);
			y2 = y + 2.0 / 3.0 * (qy1 - y);

			g->curveTo(x1, y1, x2, y2, x, y);

			// restore control point coordinate
			x1 = qx1;
			y1 = qy1;
		}
		else if (*commandIt == PathElement::CurveToQuadraticSmooth || *commandIt == PathElement::CurveToQuadraticSmoothRel)
		{
			if (SvgUtils::isCommandRelative(*commandIt))
			{
				x += cx;
				y += cy;
			}

			if (SvgUtils::isCurveToQuadratic(prevCommand))
			{
				x1 = 2 * prevX - prevX1;
				y1 = 2 * prevY - prevY1;
			}
			else
			{
				x1 = cx;
				y1 = cy;
			}

			double qx1 = x1;
			double qy1 = y1;

			x1 = cx + 2.0 / 3.0 * (qx1 - cx);
			y1 = cy + 2.0 / 3.0 * (qy1 - cy);

			x2 = x + 2.0 / 3.0 * (qx1 - x);
			y2 = y + 2.0 / 3.0 * (qy1 - y);

			g->curveTo(x1, y1, x2, y2, x, y);

			// restore control point coordinate
			x1 = qx1;
			y1 = qy1;
		}
		else if (*commandIt == PathElement::ClosePath)
		{
			g->closePath();
		}

		prevX = x;
		prevY = y;
		prevX1 = x1;
		prevY1 = y1;
		prevX2 = x2;
		prevY2 = y2;
		prevCommand = *commandIt++;
	}
}