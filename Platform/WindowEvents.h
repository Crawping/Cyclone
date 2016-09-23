/* CHANGELOG
 * Written by Josh Grooms on 20160923
 */

#pragma once
#include "Math/Vector2.h"



namespace Cyclone
{
    namespace
    {
        using namespace Utilities;
    }

    namespace Platform
    {
        struct PointerMotion
        {
            Vector2 PointerPosition;
            Vector2 PointerPositionDelta;
        };
    }
}
