#pragma once

#include <string>
#include <vector>

class GraphicsContext;

class SvgPath
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
    
    SvgPath(const std::string &str);
    
    const PathData &getPathData() const;
    void render(GraphicsContext *g);

    bool isOk() const;
    std::string getLastError() const;
    
private:
    PathData data;

    bool ok;
    std::string lastError;
};