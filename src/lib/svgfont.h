#pragma once

#include "svgglyph.h"
#include <wx/string.h>

#include <map>

class SVGPATHAPI SvgFont
{
public:
	SvgFont(const wxString &filename = wxEmptyString);

	bool LoadFromFile(const wxString &filename);
	wxString GetLastError() const;
	bool IsOk() const;

	void Clear();

	wxString GetId() const;
	int GetHorizAdvX() const;
	int GetUnitsPerEm() const;
	int GetAscent() const;
	int GetDescent() const;

	const SvgGlyph &GetGlyph(const wxString &unicode) const;
	const SvgGlyph &GetGlyph(int code) const;

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