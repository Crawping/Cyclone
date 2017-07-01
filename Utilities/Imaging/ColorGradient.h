/* CHANGELOG
 * Written by Josh Grooms on 20161106
 */

#pragma once
#include "Enumerator.h"
#include "UtilitiesAPI.h"
#include "Collections/List.h"
#include "Collections/Array.h"
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
                
                /** PROPERTIES **/
                /// <summary> Gets the number of color stops present in the gradient. </summary>
                uint Count()                                const { return _stops.size(); }
                /// <summary> Gets whether the gradient contains no color stops. </summary>
                bool IsEmpty()                              const { return Count() == 0; }

                GradientShapes Shape()                      const { return _shape; }

                ColorGradient& Shape(GradientShapes value)  { _shape = value; return *this; }
                
                

                /** CONSTRUCTORS **/
                /// <summary> Constructs a new empty color gradient to which colors can be added manually. </summary>
                UtilitiesAPI ColorGradient();
                /// <summary> Constructs a new color gradient that initialized with a list of color stops. </summary>
                /// <param name="values"> A list of <see cref="ColorStop"/> elements used to initialize the gradient. </param>
                UtilitiesAPI ColorGradient(std::initializer_list<ColorStop> values);



                /** UTILITIES **/
                /// <summary> Removes all color stops in the gradient and resets it to an empty state. </summary>
                void Clear()                                        { _stops.clear(); }
                /// <summary> Inserts a new color stop into the gradient. </summary>
                /// <param name="color"> A <see cref="ColorStop"/> element to be inserted into the gradient. </param>
                void Insert(const ColorStop& color)                 { _stops[color.Position] = color.Color; }
                /// <summary> Inserts a new color stop into the gradient. </summary>
                /// <param name="position"> A normalized position between [0.0f, 1.0f] dictating where in the gradient <paramref name="color"/> will be inserted. </param>
                /// <param name="color"> A color to be inserted into the gradient. </param>
                void Insert(float position, const Color4& color)    { Insert({ position, color }); }
                /// <summary> Removes a color stop from the gradient. </summary>
                /// <param name="position"> A normalized position between [0.0f, 1.0f] dictating which color stop will be removed. </param>
                void Remove(float position)
                {
                    if (_stops.count(position))
                        _stops.erase(position);
                }



                /** OPERATORS **/
                UtilitiesAPI const Color4& operator ()(float idx) const;
                UtilitiesAPI Vector<Color4> ToVector(uint count = 256) const;


            private:

                GradientShapes          _shape;
                std::map<float, Color4> _stops;
                
        };
    }
}
