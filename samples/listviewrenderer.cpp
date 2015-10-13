#include "listviewrenderer.h"

#include "wx/dcclient.h"

ListViewRenderer::ListViewRenderer(): wxDataViewCustomRenderer(L"wxDataViewIconText", wxDATAVIEW_CELL_INERT, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL)
{

}

bool ListViewRenderer::SetValue(const wxVariant &value)
{
	this->value << value;
	return true;
}

bool ListViewRenderer::GetValue(wxVariant& WXUNUSED(value)) const
{
	return false;
}	

bool ListViewRenderer::Render(wxRect rect, wxDC *dc, int state)
{
	const wxIcon& icon = value.GetIcon();

	int xOffset = leftMargin;

    if (icon.IsOk())
    {
    	int yOffset = (rect.GetHeight() - icon.GetHeight()) / 2;

        dc->DrawIcon(icon, rect.x + iconOffset, rect.y + yOffset);
        xOffset = iconOffset + icon.GetWidth() + iconRightMargin;
    }

    wxFont font = dc->GetFont();
	font.SetWeight(icon.IsOk() ? wxFONTWEIGHT_NORMAL : wxFONTWEIGHT_BOLD);

	int yOffset = (rect.GetHeight() - dc->GetCharHeight()) / 2;

	dc->SetFont(font);
	dc->DrawText(value.GetText(), xOffset, rect.y + yOffset);

	return true;
}

wxSize ListViewRenderer::GetSize() const
{
	int width = leftMargin;

	if (value.GetIcon().IsOk())
		width += iconOffset + value.GetIcon().GetWidth() + iconRightMargin;

	if (!value.GetText().IsEmpty())
		width += GetTextExtent(value.GetText()).GetWidth();

	return wxSize(std::max(width, 80), 20);
}

bool ListViewRenderer::HasEditorCtrl() const
{
	return false;
}