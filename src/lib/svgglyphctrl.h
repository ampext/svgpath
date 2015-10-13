#pragma once

#include "svgpathctrlbase.h"
#include "svgglyph.h"

#include <wx/bitmap.h>

class wxGraphicsContext;

class SVGPATHAPI SvgGlyphCtrl: public SvgPathCtrlBase
{
DECLARE_DYNAMIC_CLASS(SvgGlyphCtrl)

public:
	SvgGlyphCtrl() {}

	SvgGlyphCtrl(wxWindow *parent,
				wxWindowID id,
				const SvgGlyph &glyph,
				int fontSize,
				int alignment = wxALIGN_CENTER_HORIZONTAL | wxALIGN_BOTTOM,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				const wxString &name = "SvgGlyphCtrl")
	{
		Create(parent, id, glyph, fontSize, alignment, pos, size, name);
	}

	~SvgGlyphCtrl() override {}

	bool Create(wxWindow *parent,
				wxWindowID id,
				const SvgGlyph &glyph,
				int fontSize,
				int alignment,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				const wxString &name = "SvgGlyphCtrl");

	void OnPaint(wxPaintEvent& event) override;
	void OnResize(wxSizeEvent &event) override;
	wxSize GetMinClientSize() const override;
	wxSize GetMinSize() const override;

	static void RenderGlyph(wxGraphicsContext *gc, const wxRect &rect, const SvgPath &svgPath, const SvgGlyph &glyph, int size);

public:
	void SetFontSize(int size);
	int GetFontSize() const;

	void SetPadding(int padding);
	int GetPadding() const;

	void SetAlignment(int alignment);
	int GetAlignment() const;

	// TODO: SetGlyph/GetGlyph methods

	void SetColor(const wxColor &color) override;

private:
	void CreateBitmap() const;

private:
	SvgGlyph svgGlyph;
	mutable wxBitmap glyphBitmap;

	int fontSize = 14;
	int padding = 0;
	int alignment = wxALIGN_CENTER_HORIZONTAL | wxALIGN_BOTTOM;
};
