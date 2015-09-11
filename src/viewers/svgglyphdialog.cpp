#include "svgglyphdialog.h"
#include <svgglyphctrl.h>

#include <wx/sizer.h>
#include <wx/panel.h>

#include <limits>

SvgGlyphDialog::SvgGlyphDialog(wxWindow *parent): wxDialog(parent, wxID_ANY, wxEmptyString,
	wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	// test glyph fron fontawesome
	SvgGlyph glyph;
	glyph.data = "M768 896q0 106 -75 181t-181 75t-181 -75t-75 -181t75 -181t181 -75t181 75t75 181zM1024 896q0 -109 -33 -179l-364 -774q-16 -33 -47.5 -52t-67.5 -19t-67.5 19t-46.5 52l-365 774q-33 70 -33 179q0 212 150 362t362 150t362 -150t150 -362z";
	glyph.horizAdvX = 2304;
	glyph.unitsPerEm = 1024;

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	{
		sizer->Add(new SvgGlyphCtrl(this, wxID_ANY, glyph), 1, wxALL | wxEXPAND, 5);
	}

	SetSizer(sizer);

	SetSize(400, 400);
	SetLabel(L"SVG Glyph Viewer");
}