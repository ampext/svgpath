#pragma once

#include "defs.h"
#include <wx/string.h>
#include <cmath>

struct SVGPATHAPI SvgGlyph
{
	wxString unicode;
	wxString data;
	int horizAdvX = -1;
	int unitsPerEm = -1;
	int ascent = 0;
	int descent = 0;

	bool IsOk() const
	{
		return !unicode.empty() && unitsPerEm > 0;
	}

	int GetWidth(int size) const
	{
		return horizAdvX <= 0 ? size : std::round(static_cast<double>(horizAdvX) / unitsPerEm * size);
	}

	int GetHeight(int size) const
	{
		return size;
	}

	int GetVerticalOffset(int size) const
	{
		return static_cast<double>(descent)  / unitsPerEm * size;
	}

	bool operator == (const SvgGlyph &glyph) const
	{
		return unicode == unicode && data == data;
	}

	bool operator != (const SvgGlyph &glyph) const
	{
		return !(*this == glyph);
	}
};
