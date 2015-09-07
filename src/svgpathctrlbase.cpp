#include "svgpathctrlbase.h"

bool SvgPathCtrlBase::Create(wxWindow *parent, wxWindowID id, const wxString &path, const wxPoint &pos, const wxSize &size, const wxString &name)
{
    if (!wxWindow::Create(parent, id, pos, size, 0, name))
		return false;

	Bind(wxEVT_PAINT, &SvgPathCtrlBase::OnPaint, this);
	Bind(wxEVT_ERASE_BACKGROUND, [] (wxEraseEvent& event) {});

	svgPath.setPath(path.ToStdString());

	return true;
}

wxSize SvgPathCtrlBase::DoGetBestSize() const
{
	return wxSize(200, 200);
}

wxSize SvgPathCtrlBase::GetMinSize() const
{
	return wxSize(8, 8);
}

bool SvgPathCtrlBase::IsOk() const
{
	return svgPath.isOk();
}

void SvgPathCtrlBase::SetColor(const wxColor &color)
{
	this->color = color;
	Refresh();
}

wxColor SvgPathCtrlBase::GetColor() const
{
	return color;
}