#include "svgglyphctrl.h"

#include <wx/dcclient.h>
#include <wx/graphics.h>

#ifdef wxUSE_CAIRO
	#include <cairo/cairo.h>
#endif

#include <memory>

bool SvgGlyphCtrl::Create(wxWindow *parent, wxWindowID id, const SvgGlyph &glyph, const wxPoint &pos, const wxSize &size, const wxString &name)
{
    if (!SvgPathCtrlBase::Create(parent, id, glyph.data, pos, size, name))
		return false;

	return true;
}

void SvgGlyphCtrl::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
    std::unique_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(dc));

	wxRect rect = GetClientRect();

	if (!svgPath.isOk()) return;

#ifdef wxUSE_CAIRO


#endif

}

IMPLEMENT_DYNAMIC_CLASS(SvgGlyphCtrl, SvgPathCtrlBase)
