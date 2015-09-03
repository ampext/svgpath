#pragma once

#include <wx/control.h>

class SvgPathCtrl : public wxControl
{
public:
    SvgPathCtrl(wxWindow *parent,
				wxWindowID id = wxID_ANY,
				const wxString &path,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				const wxString &name = "SvgPathCtrl")
    {
        Create(parent, id, pos, size, style, name);
    }

    ~SvgPathCtrl() override;

    bool Create(wxWindow *parent,
				wxWindowID id = wxID_ANY,
				const wxString &path,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				const wxString &name = "SvgPathCtrl");
};