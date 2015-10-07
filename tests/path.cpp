#include "helpers.h"

#include <svgpath.h>
#include <measurecontext.h>

TEST_CASE("svg path")
{
	SECTION("curve bounding rect")
	{
		double x, y, w, h;

		std::tie(x, y, w, h) = SvgUtils::getCurveBoundingRect(100, 200, 100, 100, 400, 100, 400, 200);
		CHECK(x == Approx(100));
		CHECK(y == Approx(125));
		CHECK(w == Approx(300));
		CHECK(h == Approx(75));

		std::tie(x, y, w, h) = SvgUtils::getCurveBoundingRect(100, 500, 25, 400, 475, 400, 400, 500);
		CHECK(x == Approx(91.5).epsilon(0.01));
		CHECK(y == Approx(425));
		CHECK(w == Approx(316.9).epsilon(0.01));
		CHECK(h == Approx(75));

		std::tie(x, y, w, h) = SvgUtils::getCurveBoundingRect(600, 500, 600, 350, 900, 650, 900, 500);
		CHECK(x == Approx(600));
		CHECK(y == Approx(456.7).epsilon(0.01));
		CHECK(w == Approx(300));
		CHECK(h == Approx(86.6).epsilon(0.01));
	}

	SECTION("measure context")
	{
		std::string path0 = "M 18.953846,111.36917 C 66.324518,268.74331 188.62345,321.58591 276.76349,168.78951 364.90354,15.992978 257.23257,-41.802318 190.82695,63.681096 124.42132,169.16448 -28.416832,-46.005038 18.953846,111.36917 z";
		std::string path1 = "M 10 10 l 50 50";
		double x, y, w, h;

		MeasureContext context;

		SvgPath svgPath(path0);
		svgPath.draw(&context);

	context.getBoundingRect(x, y, w, h);

		CHECK(x == Approx(10).epsilon(0.01));
		CHECK(y == Approx(10).epsilon(0.01));
		CHECK(w == Approx(300).epsilon(0.01));
		CHECK(h == Approx(250).epsilon(0.01));

		svgPath = SvgPath(path1);
		context.clear();

		svgPath.draw(&context);
		context.getBoundingRect(x, y, w, h);

		CHECK(x == Approx(10).epsilon(0.01));
		CHECK(y == Approx(10).epsilon(0.01));
		CHECK(w == Approx(50).epsilon(0.01));
		CHECK(h == Approx(50).epsilon(0.01));
	}
}
