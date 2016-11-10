/* CHANGELOG
 * Written by Josh Grooms on 20161106
 */

#pragma once
#include "Enumerator.h"
#include "UtilitiesAPI.h"
#include "Collections/List.h"
#include "Collections/Vector.h"
#include "Imaging/Color4.h"
#include "Interfaces/IDataBuffer.h"
#include "Math/Vector3.h"
#include <map>



namespace Cyclone
{
    namespace Utilities
    {

        struct ColorStop
        {
            float   Position;
            Color4  Color;
        };

        struct GradientShapes : public Enumerator
        {
            enum Shapes
            {
                Linear,
                Radial,
            };

            constexpr GradientShapes(enum Shapes t = Linear) : Enumerator((int)t) { }
        };



        class ColorGradient
        {
            public:
                
                uint Count()                                const { return _stops.size(); }
                bool IsEmpty()                              const { return Count() == 0; }
                GradientShapes Shape()                      const { return _shape; }

                ColorGradient& Shape(GradientShapes value)  { _shape = value; return *this; }
                
                


                UtilitiesAPI ColorGradient();
                UtilitiesAPI ColorGradient(std::initializer_list<ColorStop> values);




                void Clear()                                        { _stops.clear(); }
                void Insert(const ColorStop& color)                 { _stops[color.Position] = color.Color; }
                void Insert(float position, const Color4& color)    { Insert({ position, color }); }
                void Remove(float position)
                {
                    if (_stops.count(position))
                        _stops.erase(position);
                }


                UtilitiesAPI const Color4& operator ()(float idx) const;
                UtilitiesAPI Vector<Color4> ToVector(uint count = 256) const;


            private:

                GradientShapes          _shape;
                std::map<float, Color4> _stops;
                
        };
    }
}
