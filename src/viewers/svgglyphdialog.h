#pragma once

#include <svgfont.h>

#include <wx/dialog.h>
#include <wx/grid.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <vector>

class GlyphCellRenderer;

class SvgGlyphDialog: public wxDialog
{
public:
	SvgGlyphDialog(wxWindow *parent);

private:
	void OnLoadFont(const wxString &path);
	void RefreshCell(const wxGridCellCoords &coords);
	void AutoSizeGrid();

private:
	wxTextCtrl *fnCtrl = nullptr;
	wxCheckBox *namesCheck = nullptr;
	wxGrid *glyphGrid = nullptr;
	GlyphCellRenderer *cellRenderer = nullptr;

	SvgFont svgFont;
	std::vector<int> fontSizes;
	size_t fontSizeIndex;
};