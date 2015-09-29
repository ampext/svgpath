#pragma once

#include <wx/dialog.h>

struct SvgGlyph;

class GlyphPreviewDialog: public wxDialog
{
public:
	GlyphPreviewDialog(wxWindow *parent, const SvgGlyph &glyph);
};