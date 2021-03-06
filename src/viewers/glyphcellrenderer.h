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

	void SetHighlightCell(const wxGridCellCoords &coords);
	const wxGridCellCoords &GetHighlightCell() const;

	void SetFontSize(int size);
	int GetFontSize() const;

	wxSize GetDefaultCellSize();

	void ShowGlyphNames(bool show);

private:
	const std::map<wxString, SvgGlyph> &glyphs;
	int fontSize = 0;
	int padding = 0;

	wxFont labelFont;
	wxColor labelColor;
	wxColor glyphColor;
	wxColor hlColor;
	wxGridCellCoords hlCellCoords;
	bool showGlyphNames = false;
	
	// It is not good to store cache as collection of wxBitmap under Windows because each wxBitmap is GDI object
	std::map<wxString, wxBitmap> glyphCache;
};
