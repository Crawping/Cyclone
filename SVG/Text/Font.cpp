#include "NVPR.h"
#include "Text/Font.h"



namespace Cyclone
{
    namespace SVG
    {
        Font::Font(const string& name) :
            Path2D(256),
            _name(name)
        {
            nvPathGlyphRange
            (
                ID(), 
                GL_SYSTEM_FONT_NAME_NV, 
                name.c_str(),
                _style,
                0,
                256,
                GL_USE_MISSING_GLYPH_NV,
                ID(),
                0
            );
        }

    }
}