#pragma once

#include "svgpathctrlbase.h"

class SVGPATHAPI SvgPathCtrl: public SvgPathCtrlBase
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

	void OnPaint(wxPaintEvent& event) override;
	void OnResize(wxSizeEvent &event) override;

public:
	void SetPathData(const wxString &pathData);

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

private:
	int padding = 0;
	bool stroke = false;
	int strokeWidth = 1;
	bool mirror = false;
	bool fit = true;
};