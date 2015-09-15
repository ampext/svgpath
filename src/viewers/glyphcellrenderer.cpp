#include "glyphcellrenderer.h"

#include <wx/dcclient.h>
#include <wx/graphics.h>
#include <wx/settings.h>

#include <memory>

GlyphCellRenderer::GlyphCellRenderer(const std::map<wxString, SvgGlyph> &glyphs, int fontSize): glyphs(glyphs), fontSize(fontSize)
{
    labelFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    labelColor = wxBLACK->ChangeLightness(150);
}

wxGridCellRenderer *GlyphCellRenderer::Clone() const
{
	return nullptr;
}

void GlyphCellRenderer::Draw(wxGrid &grid, wxGridCellAttr &attr, wxDC &dc, const wxRect &rect, int row, int col, bool isSelected)
{
    wxGridCellRenderer::Draw(grid, attr, dc, rect, row, col, false);

	wxString value = grid.GetTable()->GetValue(row, col);
    wxString label;

	auto it = glyphs.find(value);
	if (it == glyphs.end()) return;
	
    const SvgGlyph &glyph = it->second;

    if (!glyph.isOk())
        return;

    label.Printf("%04x", glyph.unicode[0]);

    std::unique_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(static_cast<wxPaintDC&>(dc)));
	gc->SetBrush(wxBrush(*wxBLACK));

    wxRect newRect = rect;

    // Oh, crap
    if (gc->GetRenderer()->GetName() == L"cairo")
    {
        newRect.x += dc.GetDeviceOrigin().x;
        newRect.y += dc.GetDeviceOrigin().y;
    }

    newRect.height -= labelFont.GetPixelSize().GetHeight() + 2 * padding;

    SvgPath path(glyph.data.ToStdString());
    SvgGlyphCtrl::RenderGlyph(gc.get(), newRect, path, glyph, fontSize);

    gc->SetFont(labelFont, labelColor);

    double width, height, descent, externalLeading;

    gc->GetTextExtent(label, &width, &height, &descent, &externalLeading);
    gc->DrawText(label, newRect.x + (newRect.width - width) / 2, newRect.y + newRect.height + 2 * padding);
}

wxSize GlyphCellRenderer::GetBestSize(wxGrid &grid, wxGridCellAttr &attr, wxDC &dc, int row, int col)
{
    return wxSize(fontSize + padding, fontSize + labelFont.GetPixelSize().GetHeight() + 3 * padding);
}
