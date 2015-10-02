#include "svgglyphctrl.h"
#include "wxcontext.h"

#include <wx/dcclient.h>

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
	if (fontSize != size)
	{
		glyphBitmap = wxNullBitmap;
		fontSize = size;
	}
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

void SvgGlyphCtrl::SetColor(const wxColor &color)
{
	if (this->color != color)
	{
		glyphBitmap = wxNullBitmap;
		SvgPathCtrlBase::SetColor(color);
	}
}

wxSize SvgGlyphCtrl::GetMinClientSize() const
{
	wxSize size(2 * padding, 2 * padding);

	if (!svgGlyph.IsOk()) return size;

	if (!glyphBitmap.IsOk())
	{
		CreateBitmap();

		if (!glyphBitmap.IsOk())
			return size;
	}

	size.IncBy(glyphBitmap.GetWidth(), glyphBitmap.GetHeight());

	return size;
}

wxSize SvgGlyphCtrl::GetMinSize() const
{
	return GetMinClientSize();
}

void SvgGlyphCtrl::CreateBitmap() const
{
	glyphBitmap = GetBitmapForGlyph(svgGlyph, fontSize, color);
}

void SvgGlyphCtrl::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	DrawBackground(dc);

	if (!svgGlyph.IsOk())
		return;

	if (!glyphBitmap.IsOk())
	{
		CreateBitmap();

		if (!glyphBitmap.IsOk())
			return;
	}

	dc.DrawBitmap(glyphBitmap, padding, padding);
}


void SvgGlyphCtrl::OnResize(wxSizeEvent &event)
{
	Refresh();
}


IMPLEMENT_DYNAMIC_CLASS(SvgGlyphCtrl, SvgPathCtrlBase)
