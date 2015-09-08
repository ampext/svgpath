#include "svgpathctrl.h"
#include "wxcontext.h"

#include <wx/dcclient.h>
#include <wx/graphics.h>

#include <memory>

bool SvgPathCtrl::Create(wxWindow *parent, wxWindowID id, const wxString &path, const wxPoint &pos, const wxSize &size, const wxString &name)
{
    if (!SvgPathCtrlBase::Create(parent, id, path, pos, size, name))
		return false;

	return true;
}

void SvgPathCtrl::SetPathData(const wxString &pathData)
{
	svgPath.setPath(pathData.ToStdString());
	Refresh();
}

void SvgPathCtrl::SetMirror(bool mirror)
{
	this->mirror = mirror;
	Refresh();
}

bool SvgPathCtrl::IsMirror() const
{
	return mirror;
}

void SvgPathCtrl::SetFit(bool fit)
{
	this->fit = fit;
	Refresh();
}

bool SvgPathCtrl::IsFit() const
{
	return fit;
}

void SvgPathCtrl::SetPadding(int padding)
{
	this->padding = padding;
	Refresh();
}

int SvgPathCtrl::GetPadding() const
{
	return padding;
}

void SvgPathCtrl::SetStroke(bool stroke)
{
	this->stroke = stroke;
	Refresh();
}

bool SvgPathCtrl::IsStroke() const
{
	return stroke;
}

void SvgPathCtrl::SetStrokeWidth(double width)
{
	strokeWidth = width;
	Refresh();
}

double SvgPathCtrl::GetStrokeWidth() const
{
	return strokeWidth;
}

void SvgPathCtrl::OnResize(wxSizeEvent &event)
{
	Refresh();
}

void SvgPathCtrl::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	DrawBackground(dc);

    std::unique_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(dc));

	wxRect rect = GetClientRect();
	rect.Deflate(padding, padding);

	if (!svgPath.isOk()) return;

	wxContext pathContext(gc.get());
	svgPath.render(&pathContext);

	double x, y, width, height;
    pathContext.getBoundingRect(x, y, width, height);

    double scale = 1.0;

    if (fit)
    {
	    double clientRatio = static_cast<double>(rect.GetWidth()) / rect.GetHeight();
	    double pathRatio = width / height;

	    if (clientRatio < pathRatio) scale = rect.GetWidth() / width;
	    else scale = rect.GetHeight() / height;
    }

    if (mirror)
    {
		gc->Translate(padding, padding + rect.GetHeight());
		gc->Scale(1.0, -1.0);
    }

    gc->Scale(scale, scale);
    gc->Translate(-x, -y);

    if (stroke)
    {
		gc->SetPen(wxPen(color, 1));
		pathContext.stroke();
    }
    else
    {
    	gc->SetBrush(wxBrush(color));
    	pathContext.fill();
    }

}

IMPLEMENT_DYNAMIC_CLASS(SvgPathCtrl, SvgPathCtrlBase)
