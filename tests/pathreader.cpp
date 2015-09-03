#include "helpers.h"

TEST_CASE("readers")
{
	SECTION("reading numbers")
	{	
		CHECK(readNumber("123") == Approx(123));
		CHECK(readNumber("1.23") == Approx(1.23));
		CHECK(readNumber("1.1e3") == Approx(1.1e3));
		CHECK(readNumber("1.1e-3") == Approx(1.1e-3));
		
		CHECK(readNumber("-123") == Approx(-123));
		CHECK(readNumber("-1.23") == Approx(-1.23));
		CHECK(readNumber("-1.1e3") == Approx(-1.1e3));
		CHECK(readNumber("-1.1e-3") == Approx(-1.1e-3));
		
		CHECK(readNumber(" \t\n1.23") == Approx(1.23));
		CHECK(readNumber("1.23 \t\n") == Approx(1.23));
		CHECK(readNumber("1.23 abc") == Approx(1.23));
		CHECK(readNumber("1.23abc") == Approx(1.23));
		
		CHECK_THROWS(readNumber("abc"));
		CHECK_THROWS(readNumber(""));
	}
	
	SECTION("reading coordinates")
	{
		double x;
		double y;
		
		CHECK_NOTHROW(std::tie(x, y) = readCoordinate("123 456"));
		CHECK(x == Approx(123));
		CHECK(y == Approx(456));
		
		CHECK_NOTHROW(std::tie(x, y) = readCoordinate("1.23 4.56"));
		CHECK(x == Approx(1.23));
		CHECK(y == Approx(4.56));
		
		CHECK_NOTHROW(std::tie(x, y) = readCoordinate("123,456"));
		CHECK(x == Approx(123));
		CHECK(y == Approx(456));
		
		CHECK_NOTHROW(std::tie(x, y) = readCoordinate("123, 456"));
		CHECK(x == Approx(123));
		CHECK(y == Approx(456));
		
		CHECK_NOTHROW(std::tie(x, y) = readCoordinate(" \t\n123, \t\n456"));
		CHECK(x == Approx(123));
		CHECK(y == Approx(456));
		
		CHECK_THROWS(readCoordinate("123"));
		CHECK_THROWS(readCoordinate("123,"));
		CHECK_THROWS(readCoordinate("abc"));
	}

	SECTION("reading moveTo command")
	{
		std::vector<SvgPath::PathElement> commands;
		std::vector<double> coords;

		CHECK_NOTHROW(readSvgCommand("M 10 20", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::MoveTo }));
		CHECK_THAT(coords, Equals({ 10, 20 }));

		commands.clear();
		coords.clear();

		CHECK_NOTHROW(readSvgCommand("m 10 20", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::MoveToRel }));
		CHECK_THAT(coords, Equals({ 10, 20 }));

		commands.clear();
		coords.clear();

		CHECK_NOTHROW(readSvgCommand("M 10, 20", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::MoveTo }));
		CHECK_THAT(coords, Equals({ 10, 20 }));

		commands.clear();
		coords.clear();

		CHECK_NOTHROW(readSvgCommand("M10,20", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::MoveTo }));
		CHECK_THAT(coords, Equals({ 10, 20 }));

		commands.clear();
		coords.clear();

		CHECK_THROWS(readSvgCommand("M 10", commands, coords));
		CHECK_THROWS(readSvgCommand("M,10", commands, coords));
		CHECK_THROWS(readSvgCommand("M 10,,10", commands, coords));
	}

	SECTION("reading lineTo commands")
	{
		std::vector<SvgPath::PathElement> commands;
		std::vector<double> coords;

		CHECK_NOTHROW(readSvgCommand("L 10 20", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::LineTo }));
		CHECK_THAT(coords, Equals({ 10, 20 }));

		CHECK_NOTHROW(readSvgCommand("l 10 20", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::LineToRel }));
		CHECK_THAT(coords, Equals({ 10, 20 }));

		CHECK_NOTHROW(readSvgCommand("L 10, 20", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::LineTo }));
		CHECK_THAT(coords, Equals({ 10, 20 }));

		CHECK_NOTHROW(readSvgCommand("L10,20", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::LineTo }));
		CHECK_THAT(coords, Equals({ 10, 20 }));

		CHECK_THROWS(readSvgCommand("L 10", commands, coords));
		CHECK_THROWS(readSvgCommand("L,10", commands, coords));

		CHECK_NOTHROW(readSvgCommand("H 10", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::LineToHorizontal }));
		CHECK_THAT(coords, Equals({ 10 }));

		CHECK_NOTHROW(readSvgCommand("h 10", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::LineToHorizontalRel }));
		CHECK_THAT(coords, Equals({ 10 }));

		CHECK_NOTHROW(readSvgCommand("V 10", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::LineToVertical }));
		CHECK_THAT(coords, Equals({ 10 }));

		CHECK_NOTHROW(readSvgCommand("v 10", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::LineToVerticalRel }));
		CHECK_THAT(coords, Equals({ 10 }));
	}

	SECTION("reading curveTo commands")
	{
		std::vector<SvgPath::PathElement> commands;
		std::vector<double> coords;

		CHECK_NOTHROW(readSvgCommand("C 10 20 30 40 50 60", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::CurveToCubic }));
		CHECK_THAT(coords, Equals({ 10, 20, 30, 40, 50, 60 }));

		CHECK_NOTHROW(readSvgCommand("c 10 20 30 40 50 60", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::CurveToCubicRel }));

		CHECK_NOTHROW(readSvgCommand("C10,20 30,40 50,60", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::CurveToCubic }));
		CHECK_THAT(coords, Equals({ 10, 20, 30, 40, 50, 60 }));

		CHECK_NOTHROW(readSvgCommand("S 10 20 30 40", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::CurveToCubicSmooth }));
		CHECK_THAT(coords, Equals({ 10, 20, 30, 40 }));

		CHECK_NOTHROW(readSvgCommand("s 10 20 30 40", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::CurveToCubicSmoothRel }));
		CHECK_THAT(coords, Equals({ 10, 20, 30, 40 }));

		CHECK_NOTHROW(readSvgCommand("Q 10 20 30 40", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::CurveToQuadratic }));
		CHECK_THAT(coords, Equals({ 10, 20, 30, 40 }));

		CHECK_NOTHROW(readSvgCommand("q 10 20 30 40", commands, coords));
		CHECK(commands == PathElements({ SvgPath::PathElement::CurveToQuadraticRel }));
		CHECK_THAT(coords, Equals({ 10, 20, 30, 40 }));

		CHECK_THROWS(readSvgCommand("C 10 20", commands, coords));
		CHECK_THROWS(readSvgCommand("c 10 20", commands, coords));
		CHECK_THROWS(readSvgCommand("S 10 20", commands, coords));
		CHECK_THROWS(readSvgCommand("s 10 20", commands, coords));

		CHECK_THROWS(readSvgCommand("Q 10 20", commands, coords));
		CHECK_THROWS(readSvgCommand("q 10 20", commands, coords));
		CHECK_THROWS(readSvgCommand("T 10", commands, coords));
		CHECK_THROWS(readSvgCommand("t 10", commands, coords));
	}

	SECTION("1+ command arguments")
	{
		std::vector<SvgPath::PathElement> commands;
		std::vector<double> coords;

		CHECK_NOTHROW(readSvgCommand("L 10,20 30,40 50,60", commands, coords));
		CHECK(commands == PathElements(
		{
			SvgPath::PathElement::LineTo,
			SvgPath::PathElement::LineTo,
			SvgPath::PathElement::LineTo
		}));
		CHECK_THAT(coords, Equals({ 10, 20, 30, 40, 50, 60 }));

		CHECK_NOTHROW(readSvgCommand("H 10 20 30", commands, coords));
		CHECK(commands == PathElements(
		{
			SvgPath::PathElement::LineToHorizontal,
			SvgPath::PathElement::LineToHorizontal,
			SvgPath::PathElement::LineToHorizontal
		}));
		CHECK_THAT(coords, Equals({ 10, 20, 30 }));

		CHECK_NOTHROW(readSvgCommand("V 10 20 30", commands, coords));
		CHECK(commands == PathElements(
		{
			SvgPath::PathElement::LineToVertical,
			SvgPath::PathElement::LineToVertical,
			SvgPath::PathElement::LineToVertical
		}));
		CHECK_THAT(coords, Equals({ 10, 20, 30 }));

		CHECK_NOTHROW(readSvgCommand("C 10,20 30,40 50,60 70,80 90,100 110,120", commands, coords));
		CHECK(commands == PathElements(
		{
			SvgPath::PathElement::CurveToCubic,
			SvgPath::PathElement::CurveToCubic
		}));
		CHECK_THAT(coords, Equals({ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120 }));

		CHECK_NOTHROW(readSvgCommand("S 10,20 30,40 50,60 70,80", commands, coords));
		CHECK(commands == PathElements(
		{
			SvgPath::PathElement::CurveToCubicSmooth,
			SvgPath::PathElement::CurveToCubicSmooth
		}));
		CHECK_THAT(coords, Equals({ 10, 20, 30, 40, 50, 60, 70, 80 }));

		CHECK_NOTHROW(readSvgCommand("Q 10,20 30,40 50,60 70,80", commands, coords));
		CHECK(commands == PathElements(
		{
			SvgPath::PathElement::CurveToQuadratic,
			SvgPath::PathElement::CurveToQuadratic
		}));
		CHECK_THAT(coords, Equals({ 10, 20, 30, 40, 50, 60, 70, 80 }));

		CHECK_NOTHROW(readSvgCommand("T 10,20 30,40 50,60", commands, coords));
		CHECK(commands == PathElements(
		{
			SvgPath::PathElement::CurveToQuadraticSmooth,
			SvgPath::PathElement::CurveToQuadraticSmooth,
			SvgPath::PathElement::CurveToQuadraticSmooth
		}));
		CHECK_THAT(coords, Equals({ 10, 20, 30, 40, 50, 60}));
	}

	SECTION("reading svg path")
	{
		std::vector<SvgPath::PathElement> commands;
		std::vector<double> coords;

		CHECK_NOTHROW(readSvgPath("M37,17v15H14V17H37z M50,0H0v50h50V0z", commands, coords));
		CHECK(commands == PathElements(
		{
			SvgPath::PathElement::MoveTo,
			SvgPath::PathElement::LineToVerticalRel,
			SvgPath::PathElement::LineToHorizontal,
			SvgPath::PathElement::LineToVertical,
			SvgPath::PathElement::LineToHorizontal,
			SvgPath::PathElement::ClosePath,
			SvgPath::PathElement::MoveTo,
			SvgPath::PathElement::LineToHorizontal,
			SvgPath::PathElement::LineToVerticalRel,
			SvgPath::PathElement::LineToHorizontalRel,
			SvgPath::PathElement::LineToVertical,
			SvgPath::PathElement::ClosePath
		}));
		CHECK_THAT(coords, Equals({ 37, 17, 15, 14, 17, 37, 50, 0, 0, 50, 50, 0 }));

		CHECK_NOTHROW(readSvgPath("M100,200 C100,100 250,100 250,200", commands, coords));
		CHECK(commands == PathElements(
		{
			SvgPath::PathElement::MoveTo,
			SvgPath::PathElement::CurveToCubic
		}));
		CHECK_THAT(coords, Equals({ 100, 200, 100, 100,  250, 100, 250, 200 }));

		CHECK_NOTHROW(readSvgPath("M600,800 C625,700 725,700 750,800 S875,900 900,800", commands, coords));
		CHECK(commands == PathElements(
		{
			SvgPath::PathElement::MoveTo,
			SvgPath::PathElement::CurveToCubic,
			SvgPath::PathElement::CurveToCubicSmooth
		}));
		CHECK_THAT(coords, Equals({ 600, 800, 625, 700, 725, 700, 750, 800, 875, 900, 900, 800 }));
	}
}
