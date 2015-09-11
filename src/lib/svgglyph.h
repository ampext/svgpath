#pragma once

#include "defs.h"
#include <wx/string.h>

struct SVGPATHAPI SvgGlyph
{
	wxString unicode;
	wxString data;
	int horizAdvX = -1;
	int unitsPerEm = -1;

	bool isOk() const
	{
		return !unicode.empty() &&  horizAdvX > 0 && unitsPerEm > 0;
	}
};