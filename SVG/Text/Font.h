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

                /** PROPERTIES **/
                /// <summary> Gets the name of the typeface that the font object represents. </summary>
                const string& Name()    const { return _name; }
                /// <summary> Gets an enumerator representing the styling that is applied to the font when rendered. </summary>
                FontStyles Style()      const { return _style; }



                /** CONSTRUCTOR **/
                /// <summary> Constructs a new object containing the entire collection of characters that make up a specific font family. </summary>
                /// <param name="name"> The name of the system font to be loaded. </param>
                SVGAPI Font(const string& name);



                /** UTILITIES **/
                /// <summary> An empty implementation that prevents frivolously rendering an entire character collection. </summary>
                void Fill()     const override { }
                void Stroke()   const override { }
                //SVGAPI void Render() const override { }

            private:

                /** PROPERTY DATA **/
                string      _name;
                FontStyles  _style;

        };
    }
}
