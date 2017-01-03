#include "NVPR.h"
#include "Collections/Vector.h"
#include "Spatial/Volume.h"
#include "Text/Font.h"



namespace Cyclone
{
    namespace SVG
    {
        /** PROPERTIES **/
        Font& Font::FontStyle(FontStyles value)
        {
            _fontStyle = value;
            NeedsUpdate = true;
            return *this;
        }



        Font::Font(const string& name) :
            Path2D(256),
            _name(name),
            _pixelsPerEm(16),
            NeedsUpdate(true)
        {
            UpdateGlyphs();

            Vector<float, 4> metrics(0);
            nvGetPathMetricRange
            (
                GL_FONT_X_MIN_BOUNDS_BIT_NV | GL_FONT_X_MAX_BOUNDS_BIT_NV | GL_FONT_Y_MIN_BOUNDS_BIT_NV | GL_FONT_Y_MAX_BOUNDS_BIT_NV,
                ID(),
                1, 0,
                &metrics(0)
            );

            Volume newBounds = Geometry().Bounds();
            newBounds.Width = metrics(2) - metrics(0);
            newBounds.Height = metrics(3) - metrics(1);
            _geometry.Bounds(newBounds);
        }


        void Font::Update() const
        {
            if (NeedsUpdate)
                UpdateGlyphs();

            NeedsUpdate = false;
            Path2D::Update();
        }

        void Font::UpdateGlyphs() const
        {
            nvPathGlyphRange
            (
                ID(),
                GL_SYSTEM_FONT_NAME_NV,
                Name().c_str(),
                FontStyle(),
                0,
                256,
                GL_USE_MISSING_GLYPH_NV,
                ID(),
                PixelsPerEm()
            );
        }
    }
}
