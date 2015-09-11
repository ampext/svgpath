#pragma once

#include "svgglyph.h"
#include <wx/string.h>

class SVGPATHAPI SvgFont
{
public:
	bool LoadFromFile(const wxString &filename);
	void Foo() {}
};