#pragma once

#include "defs.h"
#include <string>

struct SVGPATHAPI SvgGlyph
{
	std::string data;
	int horizAdvX;
	int unitsPerEm;

	SvgGlyph(const std::string &data = "", int horizAdvX = -1, int unitsPerEm = -1): data(data), horizAdvX(horizAdvX), unitsPerEm(unitsPerEm)
	{

	}

	bool isOk() const
	{
		return !data.empty() &&  horizAdvX > 0 && unitsPerEm > 0;
	}
};