#pragma once

#include <svgfont.h>

#include <wx/dialog.h>
#include <wx/grid.h>
#include <wx/textctrl.h>

class SvgGlyphDialog: public wxDialog
{
public:
	SvgGlyphDialog(wxWindow *parent);

private:
	void OnLoadFont(const wxString &path);

private:
	wxTextCtrl *fnCtrl = nullptr;
	wxGrid *glyphGrid = nullptr;

	SvgFont svgFont;
	int fontSize = 14; // defaut font size
};