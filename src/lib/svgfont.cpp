#include "svgfont.h"

#include <cmath>
#include <algorithm>

#include <wx/xml/xml.h>

SvgFont::SvgFont(const wxString &filename)
{
	if (!filename.IsEmpty())
		LoadFromFile(filename);
}

bool SvgFont::LoadFromFile(const wxString &filename)
{
	Clear();

	wxXmlDocument doc;

	if (!doc.Load(filename) || !doc.IsOk())
	{
		lastError = wxString::Format("fail to load file \"%s\"", filename);
		return false;
	}
	
	wxXmlNode *rootNode = doc.GetRoot();

	if (rootNode == NULL || rootNode->GetName() != L"svg")
	{
		lastError = wxString::Format("no <svg> node");
		return false;
	}

	wxXmlNode *node = rootNode->GetChildren();
	wxXmlNode *defsNode = nullptr;

	while (node && !defsNode)
	{
		if (node->GetName() == L"defs")
			defsNode = node;

		node = node->GetNext();
	}

	if (!defsNode)
	{
		lastError = "no <defs> node";
		return false;
	}

	node = defsNode->GetChildren();
	wxXmlNode *fontNode = nullptr;

	while (node && !fontNode)
	{
		if (node->GetName() == L"font")
			fontNode = node;

		node = node->GetNext();
	}

	if (!fontNode)
	{
		lastError = "no <font> node";
		return false;
	}

	wxString str;

	auto toInteger = [] (const wxString &str, int *value) -> bool
	{
		long lvalue;

		if (str.ToLong(&lvalue))
		{
			*value = static_cast<int>(lvalue);
			return true;
		}

		return false;
	};

	id = fontNode->GetAttribute("id");

	if (fontNode->GetAttribute("horiz-adv-x", &str))
		toInteger(str, &horizAdvX);

	node = fontNode->GetChildren();

	while (node)
	{
		if (node->GetName() == "font-face")
		{
			if (node->GetAttribute("units-per-em", &str))
				toInteger(str, &unitsPerEm);

			if (node->GetAttribute("ascent", &str))
				toInteger(str, &ascent);

			if (node->GetAttribute("descent", &str))
				toInteger(str, &descent);
		}
		else if (node->GetName() == "missing-glyph") {}
		else if (node->GetName() == "glyph")
		{
			SvgGlyph glyph;

			glyph.unicode = node->GetAttribute("unicode");
			glyph.glyphName = node->GetAttribute("glyph-name");

			if (!glyph.unicode.IsEmpty() && glyphs.count(glyph.unicode) == 0)
			{
				glyph.data = node->GetAttribute("d");

				if (node->GetAttribute("horiz-adv-x", &str))
					toInteger(str, &glyph.horizAdvX);

				glyph.unitsPerEm = unitsPerEm;
				glyph.descent = descent;
				glyph.ascent = ascent;

				glyphs[glyph.unicode] = glyph;
			}
		}

		node = node->GetNext();
	}


	return true;
}

wxString SvgFont::GetLastError() const
{
	return lastError;
}

bool SvgFont::IsOk() const
{
	return GetLastError().IsEmpty();
}

void SvgFont::Clear() 
{
	id = wxEmptyString;
	lastError = wxEmptyString;
	glyphs.clear();
	horizAdvX = -1;
	unitsPerEm = -1;
	ascent = -1;
	descent = -1;
}

wxString SvgFont::GetId() const
{
	return id;
}

int SvgFont::GetHorizAdvX() const
{
	return horizAdvX;
}

int SvgFont::GetUnitsPerEm() const
{
	return unitsPerEm;
}

int SvgFont::GetAscent() const
{
	return ascent;
}

int SvgFont::GetDescent() const
{
	return descent;
}

const SvgGlyph &SvgFont::GetGlyph(const wxString &unicode) const
{
	auto it = glyphs.find(unicode);

	if (it != glyphs.end())
		return it->second;

	return dummyGlyph;
}

const SvgGlyph &SvgFont::GetGlyph(int code) const
{
	return GetGlyph(wxString({ static_cast<wchar_t>(code) }));
}

const SvgGlyph &SvgFont::GetGlyphByName(const wxString &name) const
{
	auto it = std::find_if(glyphs.begin(), glyphs.end(), [name] (const std::pair<wxString, SvgGlyph> &p)
	{
		return p.second.glyphName == name;
	});

	if (it != glyphs.end()) return it->second;
	return dummyGlyph;
}

const std::map<wxString, SvgGlyph> &SvgFont::GetGlyphs() const
{
	return glyphs;
}