#include "NVPR.h"
#include "Collections/Vector.h"
#include "Text/Font.h"



namespace Cyclone
{
    namespace SVG
    {
        /** PROPERTIES **/
        Font& Font::Style(FontStyles value)
        {
            _style = value;
            ParamsNeedUpdate(true);
            return *this;
        }



        Font::Font(const string& name) :
            Path2D(256),
            _name(name),
            _pixelsPerEm(16)
        {
            nvPathGlyphRange
            (
                ID(), 
                GL_SYSTEM_FONT_NAME_NV, 
                name.c_str(),
                Style(),
                0,
                256,
                GL_USE_MISSING_GLYPH_NV,
                ID(),
                PixelsPerEm()
            );

            Vector<float, 4> metrics(0);
            nvGetPathMetricRange
            (
                GL_FONT_X_MIN_BOUNDS_BIT_NV | GL_FONT_X_MAX_BOUNDS_BIT_NV | GL_FONT_Y_MIN_BOUNDS_BIT_NV | GL_FONT_Y_MAX_BOUNDS_BIT_NV,
                ID(),
                1, 0,
                &metrics(0)
            );

            _glyphBounds = Vector2(metrics(2) - metrics(0), metrics(3) - metrics(1));
        }




        void Font::UpdateParameters() const
        {
            if (!ParamsNeedUpdate()) { return; }

            nvPathGlyphRange
            (
                ID(),
                GL_SYSTEM_FONT_NAME_NV,
                Name().c_str(),
                Style(),
                0,
                256,
                GL_USE_MISSING_GLYPH_NV,
                ID(),
                PixelsPerEm()
            );
        }
    }
}