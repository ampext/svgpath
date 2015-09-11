#include "svgpathdialog.h"

#include <wx/app.h>


class SvgPathViewer: public wxApp
{
public:
	virtual bool OnInit()
	{
		if(!wxApp::OnInit()) return false;

		SvgPathDialog dlg(nullptr);
		dlg.ShowModal();

		return false;
	}
	
	int OnExit()
	{
		return 0;
	}
};

IMPLEMENT_APP(SvgPathViewer)
