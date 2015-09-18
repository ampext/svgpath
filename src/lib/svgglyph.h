#pragma once

#include "defs.h"
#include <wx/string.h>

struct SVGPATHAPI SvgGlyph
{
	wxString unicode;
	wxString data;
	int horizAdvX = -1;
	int unitsPerEm = -1;
	int ascent = 0;
	int descent = 0;

	bool isOk() const
	{
		return !unicode.empty() && unitsPerEm > 0;
	}

	int getWidth(int size) const
	{
		return horizAdvX <= 0 ? size : std::round(static_cast<double>(horizAdvX) / unitsPerEm * size);
	}

	int getHeight(int size) const
	{
		return size;
	}

	int getVerticalOffset(int size) const
	{
		return static_cast<double>(descent)  / unitsPerEm * size;
	}
};
