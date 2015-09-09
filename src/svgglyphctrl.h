#pragma once

#include "svgpathctrlbase.h"
#include "svgglyph.h"

class wxGraphicsContext;

class SvgGlyphCtrl: public SvgPathCtrlBase
{
DECLARE_DYNAMIC_CLASS(SvgGlyphCtrl)

public:
	SvgGlyphCtrl() {}

    SvgGlyphCtrl(wxWindow *parent,
				wxWindowID id,
				const SvgGlyph &glyph,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				const wxString &name = "SvgGlyphCtrl")
    {
        Create(parent, id, glyph, pos, size, name);
    }

    ~SvgGlyphCtrl() override {}

    bool Create(wxWindow *parent,
				wxWindowID id,
				const SvgGlyph &glyph,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				const wxString &name = "SvgGlyphCtrl");

	void OnPaint(wxPaintEvent& event) override;
	wxSize GetMinClientSize() const override;

	static void RenderGlyph(wxGraphicsContext *gc, const wxRect &rect, const SvgPath &svgPath, const SvgGlyph &glyph, int size);

public:
	void SetFontSize(int size);
	int GetFontSize() const;

private:
	SvgGlyph svgGlyph;
	int fontSize = 14;
	int glyphWidth = 0;
};
