#include "glyphpreviewdialog.h"

#include <svgglyphctrl.h>

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

#include <array>

GlyphPreviewDialog::GlyphPreviewDialog(wxWindow *parent, const SvgGlyph &glyph): wxDialog(parent, wxID_ANY, wxEmptyString,
	wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);

		hSizer->Add(new SvgGlyphCtrl(this, wxID_ANY, glyph, 128), 0, wxALIGN_LEFT | wxALIGN_BOTTOM, 0);
		hSizer->Add(new SvgGlyphCtrl(this, wxID_ANY, glyph, 64), 0, wxALIGN_LEFT | wxALIGN_BOTTOM, 0);
		hSizer->Add(new SvgGlyphCtrl(this, wxID_ANY, glyph, 16), 0, wxALIGN_LEFT | wxALIGN_BOTTOM, 0);

		wxFlexGridSizer *gridSize = new wxFlexGridSizer(2, 5, 5);

		gridSize->AddGrowableCol(1, 1);

		gridSize->Add(new wxStaticText(this, wxID_ANY, L"Name"), 0, wxALIGN_CENTER_VERTICAL, 0);
		gridSize->Add(new wxTextCtrl(this, wxID_ANY, glyph.glyphName, wxDefaultPosition, wxDefaultSize, wxTE_READONLY), 0, wxALIGN_CENTER_VERTICAL, 0);

		wxString unicode;
		unicode.Printf("%04x", glyph.unicode[0]);

		gridSize->Add(new wxStaticText(this, wxID_ANY, L"Unicode"), 0, wxALIGN_CENTER_VERTICAL, 0);
		gridSize->Add(new wxTextCtrl(this, wxID_ANY, unicode, wxDefaultPosition, wxDefaultSize, wxTE_READONLY), 0, wxALIGN_CENTER_VERTICAL, 0);

		sizer->Add(hSizer, 1, wxALL | wxEXPAND, 5);
		sizer->Add(gridSize, 0, wxALL | wxEXPAND, 5);
	}

	sizer->Add(CreateButtonSizer(wxOK), 0, wxALL | wxEXPAND, 5);

	SetSizerAndFit(sizer);
	SetLabel(L"Preview");
}
