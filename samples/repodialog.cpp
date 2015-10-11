#include "repodialog.h"
#include "listviewrenderer.h"

#include <svgglyphctrl.h>
#include <wxcontext.h>

#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/sizer.h>
#include <wx/panel.h>

RepoDialog::RepoDialog(wxWindow *parent): wxDialog(parent, wxID_ANY, wxEmptyString,
	wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	font = SvgFont(wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath() + wxFileName::GetPathSeparator() + L"octicons.svg");
	wxASSERT_MSG(font.IsOk(), font.GetLastError());


	wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(CreateListCtrl(), 0, wxALL | wxEXPAND, 5);
	sizer->Add(CreatePanel(), 1, wxALL | wxEXPAND, 5);

	SetSizer(sizer);
	SetTitle(L"Sample Application");
}

wxWindow *RepoDialog::CreateListCtrl()
{
	wxIcon branchIcon = BitmapToIcon(GetBitmapForGlyph(font.GetGlyph(0xf020), fontSize));
	wxIcon tagIcon = BitmapToIcon(GetBitmapForGlyph(font.GetGlyph(0xf015), fontSize));

	wxDataViewListCtrl *listCtrl = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_NO_HEADER);
	listCtrl->AppendColumn(new wxDataViewColumn(wxEmptyString, new ListViewRenderer(), 0));

	wxVector<wxVariant> row(1);

	row[0] = wxVariant(wxDataViewIconText(L"Branches"));
	listCtrl->AppendItem(row);

	row[0] = wxVariant(wxDataViewIconText(L"master", branchIcon));
	listCtrl->AppendItem(row);

	row[0] = wxVariant(wxDataViewIconText(L"beta", branchIcon));
	listCtrl->AppendItem(row);

	row[0] = wxVariant(wxDataViewIconText(L"Tags"));
	listCtrl->AppendItem(row);

	row[0] = wxVariant(wxDataViewIconText(L"1.0", tagIcon));
	listCtrl->AppendItem(row);

	row[0] = wxVariant(wxDataViewIconText(L"1.2", tagIcon));
	listCtrl->AppendItem(row);

	row[0] = wxVariant(wxDataViewIconText(L"1.4", tagIcon));
	listCtrl->AppendItem(row);

	listCtrl->SetMinSize(wxSize(150, -1));

	return listCtrl;
}

wxWindow *RepoDialog::CreatePanel()
{
	wxPanel *panel = new wxPanel(this);

	return panel;
}

wxIcon RepoDialog::BitmapToIcon(const wxBitmap& bitmap)
{
	wxIcon icon;
	icon.CopyFromBitmap(bitmap);
	return icon;
};