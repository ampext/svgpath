#pragma once

#include <svgglyphctrl.h>

#include <wx/grid.h>
#include <wx/bitmap.h>

#include <map>

class GlyphCellRenderer: public wxGridCellRenderer
{
public:
    GlyphCellRenderer(const std::map<wxString, SvgGlyph> &glyphs, int fontSize);

	wxGridCellRenderer *Clone() const override;

	void Draw(wxGrid &grid, wxGridCellAttr &attr, wxDC &dc, const wxRect &rect, int row, int col, bool isSelected) override;
	wxSize GetBestSize(wxGrid &grid, wxGridCellAttr &attr, wxDC &dc, int row, int col) override;

private:
	const std::map<wxString, SvgGlyph> &glyphs;
	int fontSize;

	wxFont labelFont;
	wxColor labelColor;
	
	// It is not good to store cache as collection of wxBitmap under Windows because each wxBitmap is GDI object
	std::map<wxString, wxBitmap> glyphCache;

	static const int padding = 4;
};
