#include "glyphpreviewdialog.h"

#include <svgglyphctrl.h>
#include <wx/sizer.h>

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

		sizer->Add(hSizer, 1, wxALL | wxEXPAND, 5);
	}

	sizer->Add(CreateButtonSizer(wxOK), 0, wxALL | wxEXPAND, 5);

	SetSizerAndFit(sizer);
	SetLabel(L"Preview");
}
