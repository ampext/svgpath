#include <wx/dataview.h>

class ListViewRenderer: public wxDataViewCustomRenderer
{
public:
	ListViewRenderer();

	bool SetValue(const wxVariant &value) override;
	bool GetValue(wxVariant& WXUNUSED(value)) const override;
	bool Render(wxRect rect, wxDC *dc, int state) override;
	wxSize GetSize() const override;
	bool HasEditorCtrl() const override;

private:
	const int iconOffset = 8;
	const int leftMargin = 2;
	const int iconRightMargin = 4;

	wxDataViewIconText value;
};
