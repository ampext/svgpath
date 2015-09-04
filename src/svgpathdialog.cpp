#include "svgpathdialog.h"
#include "svgpathctrl.h"

#include <wx/checkbox.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/panel.h>

SvgPathDialog::SvgPathDialog(wxWindow *parent): wxDialog(parent, wxID_ANY, wxEmptyString,
	wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
		{
			hSizer->Add(textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_MULTILINE), 1, wxALL | wxEXPAND);	

			wxBoxSizer *vSizer = new wxBoxSizer(wxVERTICAL);
			{
				vSizer->Add(new wxCheckBox(this, wxID_ANY, "Fit to view"), 0, wxALL | wxEXPAND);
				vSizer->Add(new wxRadioButton(this, wxID_ANY, "Fill"), 0, wxALL | wxEXPAND);
				vSizer->Add(new wxRadioButton(this, wxID_ANY, "Stroke"), 0, wxALL | wxEXPAND);

				hSizer->Add(vSizer, 0, wxALL | wxEXPAND);
			}
		}

		sizer->Add(hSizer, 0, wxALL | wxEXPAND, 5);
		sizer->Add(new SvgPathCtrl(this, wxID_ANY), 1, wxALL | wxEXPAND, 5);
	}

	SetSizer(sizer);
	SetSize(400, 400);
}