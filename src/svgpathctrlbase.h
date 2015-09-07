#pragma once

#include <wx/window.h>
#include "svgpath.h"

class SvgPathCtrlBase: public wxWindow
{
public:
	SvgPathCtrlBase() {}

	bool Create(wxWindow *parent,
				wxWindowID id,
				const wxString &path,
				const wxPoint &pos,
				const wxSize &size,
				const wxString &name);

	virtual void OnPaint(wxPaintEvent& event) = 0;

public:
	virtual bool IsOk() const;

	virtual void SetColor(const wxColor &color);
	virtual wxColor GetColor() const;
	wxSize GetMinSize() const override;

protected:
    wxSize DoGetBestSize() const override;

protected:
	SvgPath svgPath;
	wxColor color = *wxBLACK;
};