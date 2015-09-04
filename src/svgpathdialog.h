#pragma once

#include <wx/dialog.h>
#include <wx/textctrl.h>

class SvgPathCtrl;

class SvgPathDialog: public wxDialog
{
public:
	SvgPathDialog(wxWindow *parent);

private:
	SvgPathCtrl *svgPathCtrl;
	wxTextCtrl	*textCtrl;
};