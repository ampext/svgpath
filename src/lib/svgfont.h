#pragma once

#include "svgglyph.h"
#include <wx/string.h>

#include <map>

class SVGPATHAPI SvgFont
{
public:
	bool LoadFromFile(const wxString &filename);
	wxString GetLastError() const;

	wxString GetId() const;
	int GetHorizAdvX() const;
	int GetUnitsPerEm() const;
	int GetAscent() const;
	int GetDescent() const;

	const SvgGlyph &GetGlyph(const wxString &unicode) const;
	const std::map<wxString, SvgGlyph> &GetGlyphs() const;

private:
	wxString id;
	int horizAdvX = -1;
	int unitsPerEm = -1;
	int ascent = -1;
	int descent = -1;

	wxString lastError;
	std::map<wxString, SvgGlyph> glyphs;
};