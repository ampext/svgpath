#include "svgpathctrl.h"

bool SvgPathCtrl::Create(wxWindow *parent, wxWindowID id, const wxString &path, const wxPoint &pos, const wxSize &size, const wxString &name)
{
    if (!wxWindow::Create(parent, id, pos, size, 0, name))
		return false;

	return true;
}

wxSize SvgPathCtrl::DoGetBestSize() const
{
	return wxSize(200, 200);
}

void SvgPathCtrl::OnPaint(wxPaintEvent& event)
{

}

wxSize SvgPathCtrl::GetMinSize() const
{
	return wxSize(10, 10);
}

IMPLEMENT_DYNAMIC_CLASS(SvgPathCtrl, wxWindow)
