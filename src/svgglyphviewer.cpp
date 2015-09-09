#include "svgglyphdialog.h"

#include <wx/app.h>


class SvgGlyphViewer: public wxApp
{
public:
	virtual bool OnInit()
	{
		if(!wxApp::OnInit()) return false;

		SvgGlyphDialog dlg(nullptr);
		dlg.ShowModal();

		return false;
	}
	
	int OnExit()
	{
		return 0;
	}
};

IMPLEMENT_APP(SvgGlyphViewer)
