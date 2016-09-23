/* CHANGELOG
 * Written by Josh Grooms on 20160923
 */

#pragma once
#include "InputControls.h"
#include "Math/Vector2.h"



namespace Cyclone
{
    namespace
    {
        using namespace Utilities;
    }

    namespace Platform
    {
        /// <summary> An event structure containing new pointer position data. </summary>
        /// <remarks>
        ///     This event structure gets dispatched every time the pointer moves within the client area of a 
        ///     <see cref="Window3D"/> rendering window.
        /// </remarks>
        struct PointerMotionEvent
        {
            /// <summary> The new (x, y) pixel position of the pointer relative to the upper-left corner of the window's client area. </summary>
            Vector2 PointerPosition;
            /// <summary> The (x, y) change in position relative to where the pointer was before the motion event was triggered. </summary>
            Vector2 PointerPositionDelta;
        };

        /// <summary> An event structure containing information about pointer button clicks. </summary>
        struct PointerClickEvent
        {
            InputControls Button;
            InputControls Chord;
        };

        


    }
}
