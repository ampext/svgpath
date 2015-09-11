#include "svgpathdialog.h"
#include <svgpathctrl.h>

#include <wx/checkbox.h>
#include <wx/radiobut.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>

SvgPathDialog::SvgPathDialog(wxWindow *parent): wxDialog(parent, wxID_ANY, wxEmptyString,
	wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	SvgPathCtrl *svgPathCtrl = nullptr;
	wxTextCtrl	*textCtrl = nullptr;
	wxCheckBox *fitCheck = nullptr;
	wxCheckBox *mirrorCheck = nullptr;
	wxRadioButton *strokeRadio = nullptr;
	wxRadioButton *fillRadio = nullptr;

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
		{
			hSizer->Add(textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_MULTILINE), 1, wxALL | wxEXPAND);	

			wxBoxSizer *vSizer = new wxBoxSizer(wxVERTICAL);
			{
				vSizer->Add(fitCheck = new wxCheckBox(this, wxID_ANY, "Fit to view"), 0, wxALL | wxEXPAND, 5);
				vSizer->Add(mirrorCheck = new wxCheckBox(this, wxID_ANY, "Mirror"), 0, wxALL | wxEXPAND, 5);
				vSizer->Add(fillRadio = new wxRadioButton(this, wxID_ANY, "Fill"), 0, wxALL | wxEXPAND, 5);
				vSizer->Add(strokeRadio = new wxRadioButton(this, wxID_ANY, "Stroke"), 0, wxALL | wxEXPAND, 5);

				hSizer->Add(vSizer, 0, wxALL | wxEXPAND);
			}
		}

		sizer->Add(hSizer, 0, wxALL | wxEXPAND, 5);
		sizer->Add(svgPathCtrl = new SvgPathCtrl(this, wxID_ANY), 1, wxALL | wxEXPAND, 5);
	}

	fitCheck->Bind(wxEVT_CHECKBOX, [svgPathCtrl] (wxCommandEvent &event)
	{
		svgPathCtrl->SetFit(event.IsChecked());
	});

	mirrorCheck->Bind(wxEVT_CHECKBOX, [svgPathCtrl] (wxCommandEvent &event)
	{
		svgPathCtrl->SetMirror(event.IsChecked());
	});

	textCtrl->Bind(wxEVT_TEXT, [svgPathCtrl] (wxCommandEvent &event)
	{
		svgPathCtrl->SetPathData(event.GetString());
	});

	Bind(wxEVT_RADIOBUTTON, [svgPathCtrl, strokeRadio] (wxCommandEvent& event)
	{
		svgPathCtrl->SetStroke(event.GetId() == strokeRadio->GetId());
	});

	fitCheck->SetValue(true);
	svgPathCtrl->SetFit(fitCheck->IsChecked());

	mirrorCheck->SetValue(true);
	svgPathCtrl->SetMirror(mirrorCheck->IsChecked());

	fillRadio->SetValue(true);
	svgPathCtrl->SetStroke(strokeRadio->GetValue());

	SetSizer(sizer);
	SetSize(400, 400);
	SetLabel(L"SVG Path Viewer");
}