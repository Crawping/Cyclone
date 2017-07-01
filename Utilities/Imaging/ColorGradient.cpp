#include "Utilities.h"
#include "Math/Math.h"
#include "Imaging/ColorGradient.h"



namespace Cyclone
{
    namespace Utilities
    {

        /** CONSTRUCTORS **/
        ColorGradient::ColorGradient()
        {

        }
        ColorGradient::ColorGradient(std::initializer_list<ColorStop> values) :
            ColorGradient()
        {
            for (const ColorStop& s : values)
                Insert(s);
        }



        /** OPERATORS **/
        const Color4& ColorGradient::operator()(float idx) const
        {
            if (IsEmpty()) { return Color4::Transparent; }                

            idx = Math::Clamp(idx, 0.0f, 1.0f);            
            if (_stops.count(idx))
                return _stops.at(idx);

            auto lower = _stops.upper_bound(idx);
            auto upper = lower;

            if (lower == _stops.begin() || upper == _stops.end())
                return lower->second;

            --lower;
            float scale = (idx - lower->first) / (upper->first - lower->first);
            return Color4
            (
                lower->second.R + (scale * (upper->second.R - lower->second.R)),
                lower->second.G + (scale * (upper->second.G - lower->second.G)),
                lower->second.B + (scale * (upper->second.B - lower->second.B)),
                lower->second.A + (scale * (upper->second.A - lower->second.A))
            );
        }
        Vector<Color4> ColorGradient::ToVector(uint count) const
        {
            Vector<Color4> output(count);
            if (IsEmpty())
            {
                output.Fill(Color4::Transparent);
                return output;
            }

            count = Math::Max(count, 2);

            uint idx = 0;
            float step = 1.0f / (float)(count - 1);
            float end = (--_stops.end())->first;
            for (float a = 0; a <= end; a += step)
                output(idx++) = operator ()(a);

            return output;
        }


    }
}