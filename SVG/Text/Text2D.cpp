#include "NVPR.h"
#include "Utilities.h"
#include "Text/Text2D.h"



namespace Cyclone
{
    namespace SVG
    {

        /** PROPERTIES **/
        Text2D& Text2D::FontStyle(FontStyles value)
        {
            _font.Style(value);
            return *this;
        }
        Text2D& Text2D::Text(const string& value)
        {
            _text = value;
            QueryKerningValues();
            QueryTextDimensions();
            return *this;
        }



        /** CONSTRUCTOR **/
        Text2D::Text2D() :
            _font("Arial"),
            _text("")
        {

        }



        /** RENDERING UTILITIES **/
        void Text2D::Fill() const
        {
            if (!IsVisible()) { return; }

            nvStencilFillPathInstanced
            (
                _text.size(),
                NumericFormats::UByte,
                _text.c_str(),
                _font.ID(),
                FillMode(),
                ~0,
                TransformTypes::TranslateX,
                _kerning.ToArray()
            );

            nvCoverFillPathInstanced
            (
                _text.size(),
                NumericFormats::UByte,
                _text.c_str(),
                _font.ID(),
                CoverMode(),
                TransformTypes::TranslateX,
                _kerning.ToArray()
            );
        }
        void Text2D::Stroke() const
        {

        }
        void Text2D::Update() const
        {
            Path2D::Update();
            _font.Update();
        }



        /** PROTECTED UTILITIES **/
        void Text2D::QueryKerningValues()
        {
            _kerning = Vector<float>(Text().size() + 1);
            _kerning(0) = 0.0f;

            nvGetPathSpacing
            (
                GL_ACCUM_ADJACENT_PAIRS_NV,
                Text().size() + 1,
                NumericFormats::UByte,
                Text().c_str(),
                _font.ID(),
                1.0f, 1.0f,
                TransformTypes::TranslateX,
                &_kerning(1)
            );
        }
        void Text2D::QueryTextDimensions()
        {
            Vector<float> dims = Vector<float>(2 * Text().size());

            nvGetPathMetrics
            (
                GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV | GL_GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV,
                Text().size(),
                NumericFormats::UByte,
                Text().c_str(),
                _font.ID(),
                0,
                &dims(0)
            );

            float width = 0.0f;
            float height = 0.0f;
            for (uint a = 0; a < dims.Count(); a += 2)
            {
                width += dims(a);
                height = Math::Max(height, dims(a + 1));
            }

            BoundarySize(Vector3(width, _font.PixelsPerEm(), 0.0f));
        }

    }
}
