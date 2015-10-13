#pragma once

#include <svgfont.h>

#include <wx/dialog.h>


class SvgFont;

class RepoDialog: public wxDialog
{
public:
	RepoDialog(wxWindow *parent);

private:
	static wxIcon BitmapToIcon(const wxBitmap &bitmap);

	wxWindow *CreateListCtrl();
	wxWindow *CreatePanel();

	SvgFont font;
	const int fontSize = 16;
};