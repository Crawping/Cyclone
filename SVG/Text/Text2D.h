/* CHANGELOG
 * Written by Josh Grooms on 20160918
 */

#pragma once
#include "Collections/Vector.h"
#include "Geometry/Path2D.h"
#include "Math/Vector2.h"
#include "Text/Font.h"



namespace Cyclone
{
    namespace SVG
    {
        class Text2D : public Path2D
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets a numeric array that defines the spacing between individual characters of the rendered text. </summary>
                virtual const Vector<float>& Kerning()  const { return _kerning; }

                virtual const string& FontName()        const { return _font.Name(); }

                virtual FontStyles FontStyle()          const { return _font.Style(); }
                /// <summary> Gets the string of text that is being rendered. </summary>
                virtual const string& Text()            const { return _text; }

                /// <summary> Sets the string of text that is being rendered. </summary>
                SVGAPI virtual Text2D& Text(const string& value);



                /** CONSTRUCTORS **/
                SVGAPI Text2D();

                SVGAPI void Fill() const override;
                SVGAPI void Stroke() const override;

            protected:

                //SVGAPI void CoverFill()   const override;
                //SVGAPI void StencilFill() const override;

            private:
                Font            _font;
                Vector<float>   _kerning;
                string          _text;

                Vector2      YLimits;
        };
    }
}
