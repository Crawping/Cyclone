/* CHANGELOG
 * Written by Josh Grooms on 20160918
 */

#pragma once
#include "Geometry/Path2D.h"
#include "Math/Array.h"
#include "Math/Vector2.h"
#include "Text/Font.h"



namespace Cyclone
{
    namespace SVG
    {
        class Text2D : public Path2D
        {
            public:
                
                const Array<float>& Kerning() const { return _kerning; }

                const string& Text() const { return _text; }


                SVGAPI Text2D& Text(const string& text);


                SVGAPI Text2D();

                SVGAPI void Render() const override;



            private:
                Font    _font;
                string  _text;

                Array<float> _kerning;
                Vector2      YLimits;
        };
    }
}