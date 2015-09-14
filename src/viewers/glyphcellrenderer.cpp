#include "glyphcellrenderer.h"

#include <wx/dcclient.h>
#include <wx/graphics.h>

#include <memory>

GlyphCellRenderer::GlyphCellRenderer(const std::map<wxString, SvgGlyph> &glyphs, int fontSize): glyphs(glyphs), fontSize(fontSize)
{

}

wxGridCellRenderer *GlyphCellRenderer::Clone() const
{
	return nullptr;
}

void GlyphCellRenderer::Draw(wxGrid &grid, wxGridCellAttr &attr, wxDC &dc, const wxRect &rect, int row, int col, bool isSelected)
{
    wxGridCellRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);

	wxString value = grid.GetTable()->GetValue(row, col);

	auto it = glyphs.find(value);
	if (it == glyphs.end()) return;
	
    const SvgGlyph &glyph = it->second;

    if (!glyph.isOk())
        return;

    std::unique_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(static_cast<wxPaintDC&>(dc)));
	gc->SetBrush(wxBrush(*wxBLACK));

    wxRect newRect = rect;

    // Oh, crap
    if (gc->GetRenderer()->GetName() == L"cairo")
    {
        newRect.x += dc.GetDeviceOrigin().x;
        newRect.y += dc.GetDeviceOrigin().y;
    }

    SvgPath path(glyph.data.ToStdString());
    SvgGlyphCtrl::RenderGlyph(gc.get(), newRect, path, glyph, fontSize);
}

wxSize GlyphCellRenderer::GetBestSize(wxGrid &grid, wxGridCellAttr &attr, wxDC &dc, int row, int col)
{
    return wxSize(fontSize + 4, fontSize + 4);
}
