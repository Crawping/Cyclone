/* CHANGELOG
 * Written by Josh Grooms on 20161031
 */

#pragma once
#include "Imaging/Color4.h"
#include "Spatial/Area.h"
#include "Spatial/Border.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace UI
    {
        struct ControlStyle
        {
            Area        BackgroundArea;
            Color4      BackgroundColor;
            Color4      BorderColor;
            Border      BorderRadius;
            Border      BorderWidth;
            Color4      FontColor;
            string      FontName;
            float       FontSize;
            uint        FontWeight;
            Color4      ForegroundColor;
            Border      Margin;
            Border      Padding;
        };
    }
}
