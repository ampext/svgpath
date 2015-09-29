#include "glyphpreviewdialog.h"

#include <svgglyphctrl.h>
#include <wx/sizer.h>

#include <array>

GlyphPreviewDialog::GlyphPreviewDialog(wxWindow *parent, const SvgGlyph &glyph): wxDialog(parent, wxID_ANY, wxEmptyString,
	wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	std::array<SvgGlyphCtrl *, 3> glyphCtrls;

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);

		hSizer->Add(glyphCtrls[0] = new SvgGlyphCtrl(this, wxID_ANY, glyph), 0, wxALIGN_LEFT | wxALIGN_BOTTOM, 0);
		hSizer->Add(glyphCtrls[1] = new SvgGlyphCtrl(this, wxID_ANY, glyph), 0, wxALIGN_LEFT | wxALIGN_BOTTOM, 0);
		hSizer->Add(glyphCtrls[2] = new SvgGlyphCtrl(this, wxID_ANY, glyph), 0, wxALIGN_LEFT | wxALIGN_BOTTOM, 0);

		glyphCtrls[0]->SetFontSize(128);
		glyphCtrls[1]->SetFontSize(64);
		glyphCtrls[2]->SetFontSize(16);

		sizer->Add(hSizer, 1, wxALL | wxEXPAND, 5);
	}

	sizer->Add(CreateButtonSizer(wxOK), 0, wxALL | wxEXPAND, 5);

	SetSizerAndFit(sizer);
	SetLabel(L"Preview");
}
