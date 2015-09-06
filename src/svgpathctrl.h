#pragma once

#include <wx/window.h>
#include "svgpath.h"

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

	wxSize GetMinSize() const override;
	void OnPaint(wxPaintEvent& event);

public:
	void SetPathData(const wxString &pathData);
	bool IsOk() const;

	void SetMirror(bool mirror = true);
	bool IsMirror() const;

	void SetFit(bool fit = true);
	bool IsFit() const;

	void SetPadding(int padding);
	int GetPadding() const;

	void SetStroke(bool stroke = true);
	bool IsStroke() const;

	void SetStrokeWidth(double width);
	double GetStrokeWidth() const;

	void SetColor(const wxColor &color);
	wxColor GetColor() const;

protected:
    wxSize DoGetBestSize() const override;

private:
	SvgPath svgPath;

	wxColor color = *wxBLACK;
	int padding = 0;
	bool stroke = false;
	int strokeWidth = 1;
	bool mirror = false;
	bool fit = true;
};