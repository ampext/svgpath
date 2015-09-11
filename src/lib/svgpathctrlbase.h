#pragma once

#include "svgpath.h"
#include <wx/window.h>

class wxDC;

class SVGPATHAPI SvgPathCtrlBase: public wxWindow
{
public:
	SvgPathCtrlBase() {}
	~SvgPathCtrlBase() override {}

	bool Create(wxWindow *parent,
				wxWindowID id,
				const wxString &path,
				const wxPoint &pos,
				const wxSize &size,
				const wxString &name);

	virtual void OnPaint(wxPaintEvent& event) = 0;
	virtual void OnResize(wxSizeEvent &event) {}

public:
	virtual bool IsOk() const;

	virtual void SetColor(const wxColor &color);
	virtual wxColor GetColor() const;
	wxSize GetMinClientSize() const override;

protected:
    wxSize DoGetBestSize() const override;
    virtual void DrawBackground(wxDC &dc) const;

protected:
	SvgPath svgPath;
	wxColor color = *wxBLACK;
};