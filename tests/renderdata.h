#pragma once

#include <svgpath.h>

#include <vector>

std::vector<std::string> testData01 = 
{
	"M100,200 C100,100 400,100 400,200",
	"M100,500 C25,400 475,400 400,500",
	"M100,800 C175,700 325,700 400,800",
	"M600,200 C675,100 975,100 900,200",
	"M600,500 C600,350 900,650 900,500",
	"M600,800 C625,700 725,700 750,800 S875,900 900,800"
};


void draw(GraphicsContext *g, const std::string &path)
{
	SvgPath svgPath(path);
	svgPath.draw(g);
}

void draw(GraphicsContext *g, const std::vector<std::string> &paths)
{
	for (const std::string &path: paths)
	{
		SvgPath svgPath(path);
		
		if (svgPath.isOk())
			svgPath.draw(g);
	}
}