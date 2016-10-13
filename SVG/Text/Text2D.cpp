#include "GPU.h"
#include "NVPR.h"
#include "GL/OpenGL.h"
#include "Pipelines/GraphicsPipeline.h"
#include "Text/Text2D.h"



namespace Cyclone
{
    namespace SVG
    {

        /** PROPERTIES **/
        Text2D& Text2D::Text(const string& value)
        {
            _text = value;
            _kerning = Vector<float>(value.size() + 1);

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



        /** CONSTRUCTOR **/
        Text2D::Text2D() :
            _font("Arial"),
            _text("")
        {

        }



        void Text2D::Fill() const
        {
            if (!IsVisible()) { return; }
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
        }



        /** PROTECTED UTILITIES **/
        //void Text2D::CoverFill() const
        //{
        //    
        //}

        //void Text2D::StencilFill() const
        //{
        //    
        //}

    }
}
