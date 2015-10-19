#include "d2dcontext.h"

namespace
{
	D2D1_POINT_2F Point2F(double x, double y)
	{
		return D2D1::Point2F(static_cast<FLOAT>(x), static_cast<FLOAT>(y));
	}
}

D2DContext::D2DContext(ID2D1Factory *factory, ID2D1RenderTarget *rt, bool filled): factory(factory), rt(rt), filled(filled)
{
	factory->CreatePathGeometry(geometry.GetAddressOf());
	geometry->Open(sink.GetAddressOf());
	rt->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), brush.GetAddressOf());
}

void D2DContext::moveTo(double x, double y)
{
	if (figureOpened)
		sink->EndFigure(D2D1_FIGURE_END_OPEN);

	sink->BeginFigure(Point2F(x, y), filled ? D2D1_FIGURE_BEGIN_FILLED : D2D1_FIGURE_BEGIN_HOLLOW);
	figureOpened = true;

	currentPoint = Point2F(x, y);
}

void D2DContext::lineTo(double x, double y)
{
	sink->AddLine(Point2F(x, y));

	currentPoint = Point2F(x, y);
}

void D2DContext::curveTo(double x1, double y1, double x2, double y2, double x3, double y3)
{
    D2D1_BEZIER_SEGMENT segment = { Point2F(x1, y1), Point2F(x2, y2), Point2F(x3, y3) };
    sink->AddBezier(segment);

	currentPoint = Point2F(x3, y3);
}

void D2DContext::closePath()
{
	if (figureOpened)
	{
		sink->EndFigure(D2D1_FIGURE_END_OPEN);
		figureOpened = false;
	}
}

void D2DContext::getCurrentPoint(double &x, double &y)
{
	x = currentPoint.x;
	y = currentPoint.y;
}

void D2DContext::getBoundingRect(double &x, double &y, double &w, double &h) 
{
    D2D1_RECT_F rect;
    geometry->GetBounds(D2D1::Matrix3x2F::Identity(), &rect);

    x = rect.left;
    y = rect.top;
    w = rect.right - rect.left;
    h = rect.bottom - rect.top;
}

void D2DContext::flush()
{
	if (sink)
	{
		if (figureOpened)
		{
			sink->EndFigure(D2D1_FIGURE_END_OPEN);
			figureOpened = false;
		}

		sink->Close();
	}
}

void D2DContext::stroke()
{
	flush();

	rt->DrawGeometry(geometry.Get(), brush.Get(), 1.0f);	
}

void D2DContext::fill()
{
	flush();

	rt->FillGeometry(geometry.Get(), brush.Get());
}