#include "helpers.h"
#include <svgpath.h>

TEST_CASE("svg path")
{
	SECTION("bounding rect")
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
}
