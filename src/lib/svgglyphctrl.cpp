#include "svgglyphctrl.h"
#include "wxcontext.h"

#include <wx/dcclient.h>
#include <wx/graphics.h>

#include <memory>

bool SvgGlyphCtrl::Create(wxWindow *parent, wxWindowID id, const SvgGlyph &glyph, const wxPoint &pos, const wxSize &size, const wxString &name)
{
    if (!SvgPathCtrlBase::Create(parent, id, glyph.data, pos, size, name))
		return false;

	svgGlyph = glyph;

	return true;
}

void SvgGlyphCtrl::SetFontSize(int size)
{
	fontSize = size;
}

int SvgGlyphCtrl::GetFontSize() const
{
	return fontSize;
}

void SvgGlyphCtrl::SetPadding(int padding)
{
	this->padding = padding;
}

int SvgGlyphCtrl::GetPadding() const
{
	return padding;
}

wxSize SvgGlyphCtrl::GetMinClientSize() const
{
	if (svgGlyph.IsOk()) return wxSize(svgGlyph.GetWidth(fontSize) + 2 * padding, svgGlyph.GetHeight(fontSize) + 2 * padding);
	return wxSize(2 * padding, 2 * padding);
}

wxSize SvgGlyphCtrl::GetMinSize() const
{
	return GetMinClientSize();
}

void SvgGlyphCtrl::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	DrawBackground(dc);

	if (!svgPath.isOk() || !svgGlyph.IsOk())
		return;

    std::unique_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(dc));
	gc->SetBrush(wxBrush(color));

    RenderGlyph(gc.get(), GetClientRect(), svgPath, svgGlyph, fontSize);
}

void SvgGlyphCtrl::RenderGlyph(wxGraphicsContext *gc, const wxRect &rect, const SvgPath &svgPath, const SvgGlyph &glyph, int size)
{
    int width = glyph.GetWidth(size);
	int height = glyph.GetHeight(size);
    double scale = static_cast<double>(width) / (glyph.horizAdvX > 0 ? glyph.horizAdvX : glyph.unitsPerEm);

	wxContext pathContext(gc);

    double xCenterOffset = std::round(rect.x + (rect.GetWidth() - width) / 2);
    double yCenterOffset = std::round(rect.y + (rect.GetHeight() - height) / 2);

    gc->PushState();
    gc->Translate(xCenterOffset, yCenterOffset + height + glyph.GetVerticalOffset(size));
	gc->Scale(scale, -scale);

	svgPath.render(&pathContext);

	pathContext.fill();
	gc->PopState();
}

void SvgGlyphCtrl::OnResize(wxSizeEvent &event)
{
	Refresh();
}


IMPLEMENT_DYNAMIC_CLASS(SvgGlyphCtrl, SvgPathCtrlBase)
