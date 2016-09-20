#include "Text/Text2D.h"
#include "NVPR.h"

#define GL_MODELVIEW                      0x1700
#define GL_PROJECTION                     0x1701

namespace Cyclone
{
    namespace SVG
    {

        /** PROPERTIES **/
        Text2D& Text2D::Text(const string& text)
        {
            _text = text;
            _kerning = Array<float>(text.size() + 1);

            _kerning(0) = 0.0f;
            nvGetPathSpacing
            (
                GL_ACCUM_ADJACENT_PAIRS_NV,
                _text.size() + 1,
                NumericFormats::UByte,
                _text.c_str(),
                _font.ID(),
                1.0f, 1.0f,
                TransformTypes::TranslateX,
                &_kerning(1)
            );

            nvGetPathMetricRange
            (
                GL_FONT_Y_MIN_BOUNDS_BIT_NV | GL_FONT_Y_MAX_BOUNDS_BIT_NV,
                _font.ID(),
                1,
                2 * sizeof(float),
                &YLimits.X
            );

            return *this;
        }


        Text2D::Text2D() :
            _font("Arial"),
            _text("")
        {

        }

        void Text2D::Render() const
        {
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
    }
}
