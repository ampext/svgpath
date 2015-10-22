#include "svgglyphctrl.h"
#include "wxcontext.h"

#include <wx/dcclient.h>

#include <memory>

bool SvgGlyphCtrl::Create(wxWindow *parent, wxWindowID id, const SvgGlyph &glyph, int fontSize, int alignment, const wxPoint &pos, const wxSize &size, const wxString &name)
{
	if (!SvgPathCtrlBase::Create(parent, id, glyph.data, pos, size, name))
		return false;

	svgGlyph = glyph;

	this->alignment = alignment;
	this->fontSize = fontSize;

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

void SvgGlyphCtrl::SetGlyph(const SvgGlyph &glyph)
{
	if (svgGlyph != glyph)
	{
		glyphBitmap = wxNullBitmap;
		svgGlyph = glyph;		
	}
}

const SvgGlyph &SvgGlyphCtrl::GetGlyph() const
{
	return svgGlyph;
}

void SvgGlyphCtrl::SetPadding(int padding)
{
	this->padding = padding;
}

int SvgGlyphCtrl::GetPadding() const
{
	return padding;
}

void SvgGlyphCtrl::SetAlignment(int alignment)
{
	this->alignment = alignment;
}

int SvgGlyphCtrl::GetAlignment() const
{
	return alignment;
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
	glyphBitmap = GetBitmapForGlyph(svgGlyph, fontSize, color, GetBackgroundColour());
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

	wxRect rect = GetClientRect();

	int xOffset = padding;
	int yOffset = padding;

	if (alignment & wxALIGN_TOP) yOffset += (rect.GetHeight() - glyphBitmap.GetHeight());
	else if (alignment & wxALIGN_CENTER_VERTICAL) yOffset += (rect.GetHeight() - glyphBitmap.GetHeight()) / 2;

	if (alignment & wxALIGN_RIGHT) xOffset += (rect.GetWidth() - glyphBitmap.GetWidth());
	else if (alignment & wxALIGN_CENTER_HORIZONTAL) xOffset += (rect.GetWidth() - glyphBitmap.GetWidth()) / 2;

	dc.DrawBitmap(glyphBitmap, xOffset, yOffset);
}


void SvgGlyphCtrl::OnResize(wxSizeEvent &event)
{
	Refresh();
}


IMPLEMENT_DYNAMIC_CLASS(SvgGlyphCtrl, SvgPathCtrlBase)
