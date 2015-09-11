#include "helpers.h"
#include <svgfont.h>

TEST_CASE("font loader")
{
	SECTION("loading svg font")
	{
		SvgFont svgFont;
		svgFont.Foo();
		//CHECK(svgFont.LoadFromFile("font0.svg"));
	}
}