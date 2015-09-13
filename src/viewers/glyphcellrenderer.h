#pragma once

#include <svgglyphctrl.h>

#include <wx/grid.h>
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
};
