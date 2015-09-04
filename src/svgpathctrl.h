#pragma once

#include <wx/control.h>

class SvgPathCtrl: public wxWindow
{
DECLARE_DYNAMIC_CLASS(SvgPathCtrl)

public:
	SvgPathCtrl() {}

    SvgPathCtrl(wxWindow *parent,
				wxWindowID id = wxID_ANY,
				const wxString &path = wxEmptyString,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				const wxString &name = "SvgPathCtrl")
    {
        Create(parent, id, path, pos, size, name);
    }

    ~SvgPathCtrl() override {}

    bool Create(wxWindow *parent,
				wxWindowID id = wxID_ANY,
				const wxString &path = wxEmptyString,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				const wxString &name = "SvgPathCtrl");

protected:
    wxSize DoGetBestSize() const override;

public:
	wxSize GetMinSize() const override;
	void OnPaint(wxPaintEvent& event);
};