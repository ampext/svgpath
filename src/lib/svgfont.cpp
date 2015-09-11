#include "svgfont.h"

#include <wx/xml/xml.h>

bool SvgFont::LoadFromFile(const wxString &filename)
{
	wxXmlDocument doc;

	if(!doc.Load(filename)) return false;
	
	wxXmlNode *rootNode = doc.GetRoot();
	if(rootNode == NULL || rootNode->GetName() != L"svg") return false;

	wxXmlNode *itemsNode = rootNode->GetChildren();

	return true;
}