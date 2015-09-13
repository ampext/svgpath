#include "helpers.h"
#include <svgfont.h>

extern std::string executablePath;

TEST_CASE("font loader")
{
	SECTION("loading svg font")
	{
		SvgFont svgFont;

		CHECK(svgFont.LoadFromFile(executablePath + "/font0.svg"));
		CHECK(svgFont.GetLastError() == wxEmptyString);
		CHECK(svgFont.GetId() == "testfont0");
		CHECK(svgFont.GetHorizAdvX() == 14);
		CHECK(svgFont.GetUnitsPerEm() == 14);
		CHECK(svgFont.GetAscent() == 14);
		CHECK(svgFont.GetDescent() == -7);
		CHECK(svgFont.GetGlyphs().size() == 4);

		const SvgGlyph &glyphA = svgFont.GetGlyph("a");
		const SvgGlyph &glyphB = svgFont.GetGlyph("b");
		const SvgGlyph &glyphC = svgFont.GetGlyph("c");
		const SvgGlyph &glyphSpace = svgFont.GetGlyph(" ");

		CHECK(glyphA.unicode == "a");
		CHECK(glyphA.data == "d0");
		CHECK(glyphA.horizAdvX == 14);
		CHECK(glyphA.unitsPerEm == 14);

		CHECK(glyphB.unicode == "b");
		CHECK(glyphB.data == "d1");
		CHECK(glyphB.horizAdvX == 16);
		CHECK(glyphB.unitsPerEm == 14);

		CHECK(glyphC.unicode == "c");
		CHECK(glyphC.data == "d2");
		CHECK(glyphC.unitsPerEm == 14);

		CHECK(glyphSpace.unicode == " ");
		CHECK(glyphSpace.data.empty());
		CHECK(glyphSpace.unitsPerEm == 14);

		CHECK_FALSE(svgFont.LoadFromFile(executablePath + "/font1.svg"));
		CHECK(svgFont.GetLastError() != wxEmptyString);

		svgFont.Clear();
		CHECK(svgFont.GetLastError() == wxEmptyString);
	}
}