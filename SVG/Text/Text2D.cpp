#include "Text/Text2D.h"
#include "NVPR.h"

#define GL_MODELVIEW                      0x1700
#define GL_PROJECTION                     0x1701

namespace Cyclone
{
    namespace SVG
    {
        Text2D::Text2D(const string& text) : 
            _font("Arial"),
            _text(text),
            _kerning(text.size() + 1)
        {
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
        }



        void Text2D::Render() const
        {
            //nvIdentityMatrix(GL_PROJECTION);
            //nvOrthoMatrix(GL_MODELVIEW, 0, _kerning(_text.size()), YLimits.X, YLimits.Y, -1, 1);
            //nvOrthoMatrix(GL_MODELVIEW, -10, 10, -10, 10, -1, 1);

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