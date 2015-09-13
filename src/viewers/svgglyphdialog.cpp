#include "svgglyphdialog.h"
#include "glyphcellrenderer.h"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h> 
#include <wx/filename.h>

SvgGlyphDialog::SvgGlyphDialog(wxWindow *parent): wxDialog(parent, wxID_ANY, wxEmptyString,
	wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    wxButton *fnButton;

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
		{
			hSizer->Add(fnCtrl = new wxTextCtrl(this, wxID_ANY), 1, wxALL | wxEXPAND, 5);
			hSizer->Add(fnButton = new wxButton(this, wxID_ANY, "...", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT), 0, wxALL | wxEXPAND, 5);
		}

		sizer->Add(hSizer, 0, wxALL | wxEXPAND, 5);
		sizer->Add(glyphGrid = new wxGrid(this, wxID_ANY), 1, wxALL | wxEXPAND, 5);
	}

	glyphGrid->HideColLabels();
	glyphGrid->HideRowLabels();
	glyphGrid->SetColMinimalAcceptableWidth(30);
	glyphGrid->SetRowMinimalAcceptableHeight(30);
    glyphGrid->DisableCellEditControl();
    glyphGrid->SetCellHighlightPenWidth(0);
    glyphGrid->SetCellHighlightROPenWidth(0);

	fnCtrl->Disable();

	fnButton->Bind(wxEVT_BUTTON, [this] (wxCommandEvent&)
	{
		wxFileDialog fileDialog(this, L"Open SVG file", L"", L"", L"SVG files (*.svg)|*.svg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	    if (fileDialog.ShowModal() == wxID_CANCEL)
	        return;

	    this->OnLoadFont(fileDialog.GetPath());
	});

	SetSizer(sizer);
	SetSize(400, 400);
    SetLabel(L"SVG Glyph Viewer");
}

void SvgGlyphDialog::OnLoadFont(const wxString &path)
{
	glyphGrid->SetTable(nullptr);

	if (svgFont.LoadFromFile(path))
	{
		fnCtrl->SetValue(wxString::Format(L"%s (%s)", svgFont.GetId(), wxFileName::FileName(path).GetFullName()));

		int glyphCount = std::count_if(svgFont.GetGlyphs().begin(), svgFont.GetGlyphs().end(), [](const std::pair<wxString, SvgGlyph> &glyph)
		{
			return !glyph.second.data.IsEmpty();
		});

		int cols = 20;
		int rows = std::round(static_cast<float>(glyphCount) / cols + 0.5f);

		glyphGrid->CreateGrid(rows, cols, wxGrid::wxGridSelectRows);
        glyphGrid->SetDefaultRenderer(new GlyphCellRenderer(svgFont.GetGlyphs(), fontSize));

		int col = 0;
		int row = 0;
		
		for (const std::pair<wxString, SvgGlyph> &glyph: svgFont.GetGlyphs())
		{
			if (glyph.second.data.IsEmpty()) continue;

			if (col >= glyphGrid->GetNumberCols())
			{
				col = 0;
				row++;
			}

			glyphGrid->SetReadOnly(row, col, true);
            glyphGrid->SetCellValue(row, col++, glyph.first);
		}

		for (int col = 0; col < glyphGrid->GetNumberCols(); col++)
			glyphGrid->SetColSize(col, fontSize + 20);

		for (int row = 0; row < glyphGrid->GetNumberRows(); row++)
			glyphGrid->SetRowSize(row, fontSize + 20);
	}
	else
	{
		wxMessageBox(L"Can not open file", L"Error");
		fnCtrl->SetValue(wxEmptyString);
	}
}
