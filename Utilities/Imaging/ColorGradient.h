/* CHANGELOG
 * Written by Josh Grooms on 20161106
 */

#pragma once
#include "Collections/List.h"
#include "Imaging/Color4.h"
#include "Math/Vector3.h"



namespace Cyclone
{
    namespace Utilities
    {

        struct ColorStop
        {
            Color4  Color;
            Vector3 Position;
        };



        class ColorGradient
        {
            public:
                const ColorStop& First() const { return Stops.First(); }
                const ColorStop& Last() const { return Stops.Last(); }


                ColorGradient()
                {

                }
                ColorGradient(std::initializer_list<ColorStop> values)
                {
                    for (const ColorStop& s : values)
                        Stops.Append(s);
                }



                void ToMatrix() const
                {
                    ColorStop first = Stops.First();
                    ColorStop last = Stops.Last();

                    //Vector<float, 12> colorTransform =
                    //{
                    //    sqrt(first.Position.X) * (last.Color.R - first.Color.R), sqrt(0, first.Color.R,
                    //    sqrt(first.Position.X) * (last.Color.G - first.Color.G), sqrt(0, first.Color.G,
                    //    sqrt(first.Position.X) * (last.Color.B - first.Color.B), sqrt(0, first.Color.B,
                    //    sqrt(first.Position.X) * (last.Color.A - first.Color.A), sqrt(0, first.Color.A,
                    //};
                }



            private:

                List<ColorStop> Stops;

        };
    }
}
