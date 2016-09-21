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
                
                /** PROPERTIES **/
                const Array<float>& Kerning()   const { return _kerning; }

                const string& Text()            const { return _text; }

                SVGAPI Text2D& Text(const string& value);



                /** CONSTRUCTORS **/
                SVGAPI Text2D();

            protected:

                SVGAPI void Cover(const GPU* gpu) const override;
                SVGAPI void Stencil(const GPU* gpu) const override;

            private:
                Font            _font;
                Array<float>    _kerning;
                string          _text;

                Vector2      YLimits;
        };
    }
}