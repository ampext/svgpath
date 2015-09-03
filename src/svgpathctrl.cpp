#include "svgpathctrl.h"

bool SvgPathCtrl::Create(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &path, const wxPoint &pos = wxDefaultPosition,
	const wxSize &size = wxDefaultSize,	const wxString &name = "SvgPathCtrl")
{
    if (!CreateBase(parent, id, pos, size, 0, wxDefaultValidator, name))
		return false;
}