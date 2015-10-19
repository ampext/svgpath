#pragma once

#include "graphicscontext.h"

#include <d2d1.h>
#include <d2d1helper.h>
#include <wrl.h>

class SVGPATHAPI D2DContext: public GraphicsContext
{
public:
	D2DContext(ID2D1Factory *factory, ID2D1RenderTarget *rt, bool filled = true);

	void moveTo(double x, double y) override;
	void lineTo(double x, double y) override;
	void curveTo(double x1, double y1, double x2, double y2, double x3, double y3) override;
	void closePath() override;
	void getCurrentPoint(double &x, double &y) override;
	void getBoundingRect(double &x, double &y, double &w, double &h) override;

	void stroke() override;
	void fill() override;

	void flush();

private:
	ID2D1Factory *factory;
	ID2D1RenderTarget *rt;
	bool filled;

	Microsoft::WRL::ComPtr<ID2D1PathGeometry> geometry;
	Microsoft::WRL::ComPtr<ID2D1GeometrySink> sink;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush;

	D2D1_POINT_2F currentPoint;
	bool figureOpened = false;	
};
