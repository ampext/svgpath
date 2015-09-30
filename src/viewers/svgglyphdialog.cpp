#include "svgglyphdialog.h"
#include "glyphcellrenderer.h"
#include "glyphpreviewdialog.h"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h> 
#include <wx/filename.h>
#include <wx/choice.h>

 #include <algorithm>

SvgGlyphDialog::SvgGlyphDialog(wxWindow *parent): wxDialog(parent, wxID_ANY, wxEmptyString,
	wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    wxButton *fnButton;
    wxChoice *sizeChoice;

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
		{
			hSizer->Add(fnCtrl = new wxTextCtrl(this, wxID_ANY), 1, wxALL | wxEXPAND, 5);
			hSizer->Add(fnButton = new wxButton(this, wxID_ANY, "...", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT), 0, wxALL | wxEXPAND, 5);
			hSizer->Add(sizeChoice = new wxChoice(this, wxID_ANY), 0, wxALL | wxEXPAND, 5);
		}

		sizer->Add(hSizer, 0, wxALL | wxEXPAND, 5);
		sizer->Add(glyphGrid = new wxGrid(this, wxID_ANY), 1, wxALL | wxEXPAND, 5);
	}

	fontSizes = { 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36 };

	for (int size: fontSizes)
		sizeChoice->Append(wxString::Format("%d", size));

	sizeChoice->SetSelection(1);

	glyphGrid->HideColLabels();
	glyphGrid->HideRowLabels();
	glyphGrid->EnableGridLines(false);
	glyphGrid->SetColMinimalAcceptableWidth(30);
	glyphGrid->SetRowMinimalAcceptableHeight(30);
    glyphGrid->DisableCellEditControl();
    glyphGrid->SetCellHighlightPenWidth(0);
    glyphGrid->SetCellHighlightROPenWidth(0);
    glyphGrid->DisableDragGridSize();

    glyphGrid->GetGridWindow()->Bind(wxEVT_MOTION, [this] (wxMouseEvent &event)
    {
    	if (cellRenderer)
    	{
    		wxCoord x, y;
			glyphGrid->CalcUnscrolledPosition(event.GetX(), event.GetY(), &x, &y);

    		wxGridCellCoords oldCoords = cellRenderer->GetHighlightCell();
    		wxGridCellCoords newCoords = glyphGrid->XYToCell(x, y);

    		if (oldCoords != newCoords)
    		{
    			cellRenderer->SetHighlightCell(newCoords);

    			RefreshCell(oldCoords);
    			RefreshCell(newCoords);
    		}
    	}
    });

    glyphGrid->GetGridWindow()->Bind(wxEVT_LEFT_DCLICK, [this] (wxMouseEvent &event)
    {
        if (cellRenderer)
    	{
    		wxCoord x, y;
			glyphGrid->CalcUnscrolledPosition(event.GetX(), event.GetY(), &x, &y);
			wxGridCellCoords coords = glyphGrid->XYToCell(x, y);

			wxString value = glyphGrid->GetTable()->GetValue(coords.GetRow(), coords.GetCol());
			const SvgGlyph &glyph = svgFont.GetGlyph(value);

			if (glyph.IsOk())
			{
				GlyphPreviewDialog dlg(this, glyph);
				dlg.ShowModal();
			}
		}
    });

    glyphGrid->GetGridWindow()->Bind(wxEVT_LEAVE_WINDOW, [this] (wxMouseEvent &event)
    {
    	if (cellRenderer)
    	{
	    	wxGridCellCoords oldCoords = cellRenderer->GetHighlightCell();

	    	cellRenderer->SetHighlightCell(wxGridCellCoords());
	    	RefreshCell(oldCoords);
    	}
    });

	fnCtrl->Disable();

	fnButton->Bind(wxEVT_BUTTON, [this] (wxCommandEvent&)
	{
		wxFileDialog fileDialog(this, L"Open SVG file", L"", L"", L"SVG files (*.svg)|*.svg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	    if (fileDialog.ShowModal() == wxID_CANCEL)
	        return;

	    this->OnLoadFont(fileDialog.GetPath());
	});

    sizeChoice->Bind(wxEVT_CHOICE, [this, sizeChoice] (wxCommandEvent&)
	{
		int fontSize = fontSizes.at(sizeChoice->GetCurrentSelection());
		cellRenderer->SetFontSize(fontSize);
		glyphGrid->AutoSize();
		Layout();
	});

	SetSizer(sizer);
	SetSize(400, 400);
    SetLabel(L"SVG Glyph Viewer");
}

void SvgGlyphDialog::OnLoadFont(const wxString &path)
{
	glyphGrid->SetTable(nullptr);
	cellRenderer = nullptr;

	if (svgFont.LoadFromFile(path))
	{
		fnCtrl->SetValue(wxString::Format(L"%s (%s)", svgFont.GetId(), wxFileName::FileName(path).GetFullName()));

		int glyphCount = std::count_if(svgFont.GetGlyphs().begin(), svgFont.GetGlyphs().end(), [](const std::pair<wxString, SvgGlyph> &glyph)
		{
			return !glyph.second.data.IsEmpty();
		});

		int cols = 10;
		int rows = std::round(static_cast<float>(glyphCount) / cols + 0.5f);

		glyphGrid->CreateGrid(rows, cols, wxGrid:: wxGridSelectCells);
        glyphGrid->SetDefaultRenderer(cellRenderer = new GlyphCellRenderer(svgFont.GetGlyphs(), 14));

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

		glyphGrid->AutoSize();
		Layout();
	}
	else
	{
		wxMessageBox(L"Can not open file", L"Error");
		fnCtrl->SetValue(wxEmptyString);
	}
}

void SvgGlyphDialog::RefreshCell(const wxGridCellCoords &coords)
{
	wxRect rect = glyphGrid->CellToRect(coords);
	glyphGrid->CalcScrolledPosition(rect.x, rect.y, &rect.x, &rect.y);
	glyphGrid->GetGridWindow()->Refresh(false, &rect);
}
