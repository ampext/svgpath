#pragma once

#include "defs.h"

#include <string>
#include <vector>

class GraphicsContext;

class SVGPATHAPI SvgPath
{
public:
	enum class PathElement
	{
		MoveTo,
		MoveToRel,
		LineTo,
		LineToRel,
		LineToHorizontal,
		LineToHorizontalRel,
		LineToVertical,
		LineToVerticalRel,
		CurveToCubic,
		CurveToCubicRel,
		CurveToCubicSmooth,
		CurveToCubicSmoothRel,
		CurveToQuadratic,
		CurveToQuadraticRel,
		CurveToQuadraticSmooth,
		CurveToQuadraticSmoothRel,
		ClosePath
	};
	
	struct PathData
	{
		std::vector<PathElement> commands;
		std::vector<double> coords;
	};
	
public:
	
	SvgPath() {}
	SvgPath(const std::string &str);

	void setPath(const std::string &str);
	const std::string &getPath() const;
	
	const PathData &getPathData() const;
	void draw(GraphicsContext *g) const;

	bool isOk() const;
	std::string getLastError() const;
	
private:
	std::string pathString;
	PathData data;

	bool ok = false;
	std::string lastError;
};