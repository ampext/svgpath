#include "svgpathctrl.h"
#include "cairocontext.h"

#include <wx/dcclient.h>
#include <wx/graphics.h>

#ifdef wxUSE_CAIRO
	#include <cairo/cairo.h>
#endif

#include <memory>

bool SvgPathCtrl::Create(wxWindow *parent, wxWindowID id, const wxString &path, const wxPoint &pos, const wxSize &size, const wxString &name)
{
    if (!wxWindow::Create(parent, id, pos, size, 0, name))
		return false;

	Bind(wxEVT_PAINT, &SvgPathCtrl::OnPaint, this);
	Bind(wxEVT_ERASE_BACKGROUND, [] (wxEraseEvent& event) {});

	return true;
}

wxSize SvgPathCtrl::DoGetBestSize() const
{
	return wxSize(200, 200);
}

void SvgPathCtrl::SetPathData(const wxString &pathData)
{
	svgPath.setPath(pathData.ToStdString());
	Refresh();
}

bool SvgPathCtrl::IsOk() const
{
	return svgPath.isOk();
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

void SvgPathCtrl::SetColor(const wxColor &color)
{
	this->color = color;
	Refresh();
}

wxColor SvgPathCtrl::GetColor() const
{
	return color;
}

void SvgPathCtrl::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
    std::unique_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(dc));

	wxRect rect = GetClientRect();
	rect.Deflate(padding, padding);

	if (!svgPath.isOk()) return;

#ifdef wxUSE_CAIRO

    cairo_t *cr = reinterpret_cast<cairo_t *>(gc->GetNativeContext());

    CairoContext pathContext(cr);

	svgPath.render(&pathContext);

	double left, top, right, bottom;
    cairo_path_extents(cr, &left, &top, &right, &bottom);

    cairo_set_source_rgba(cr, 0, 0, 0, 0);
    cairo_stroke(cr);

    double width = right - left;
    double height = bottom - top;
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
		cairo_translate(cr, padding, padding + rect.GetHeight());
		cairo_scale(cr, 1.0, -1.0);
    }

    cairo_scale(cr, scale, scale);
    cairo_translate(cr, -left, -top);

    svgPath.render(&pathContext);

 	cairo_set_source_rgba(cr,
 		static_cast<double>(color.Red()) / 255,
 		static_cast<double>(color.Green()) / 255,
 		static_cast<double>(color.Blue()) / 255, 1);

    if (stroke)
    {
    	cairo_set_line_width(cr, strokeWidth);
    	cairo_stroke(cr);
    }
    else cairo_fill(cr);

#endif

}

wxSize SvgPathCtrl::GetMinSize() const
{
	return wxSize(10, 10);
}

IMPLEMENT_DYNAMIC_CLASS(SvgPathCtrl, wxWindow)
