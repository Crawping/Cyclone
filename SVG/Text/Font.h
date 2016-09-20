/* CHANGELOG
 * Written by Josh Grooms on 20160918
 */

#pragma once
#include "SVGAPI.h"
#include "Geometry/Path2D.h"



namespace Cyclone
{
    namespace SVG
    {
        class Font : public Path2D
        {
            public:

                const string& Name()    const { return _name; }
                FontStyles Style()      const { return _style; }



                SVGAPI Font(const string& name);


                SVGAPI void Render() const override { }


            private:

                string      _name;
                FontStyles  _style;

        };
    }
}
