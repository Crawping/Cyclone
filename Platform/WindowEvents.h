/* CHANGELOG
 * Written by Josh Grooms on 20160923
 */

#pragma once
#include "InputControls.h"
#include "Math/Vector2.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }

    namespace Platform
    {
        
        /// <summary> An event structure containing new pointer position data. </summary>
        /// <remarks>
        ///     This event structure gets dispatched every time the pointer moves within the client area of a
        ///     <see cref="Window3D"/> rendering window.
        /// </remarks>
        struct PointerMotionEvent
        {
            /// <summary> The (x, y) change in position relative to where the pointer was before the motion event was triggered. </summary>
            const Vector2& Delta;
            /// <summary> The new (x, y) pixel position of the pointer relative to the upper-left corner of the window's client area. </summary>
            const Vector2& Position;
        };

        /// <summary> An event structure containing information about pointer button clicks. </summary>
        /// <remarks>
        ///     This event structure gets dispatched every time a pointer device button is pressed or released while 
        ///     the <see cref="Window3D"/> rendering window has input focus.
        /// </remarks>
        struct PointerClickEvent
        {
            /// <summary> The specific pointer device button that has been either pressed or released. </summary>
            PointerButtons Button;
            /// <summary> The current state of all pointer device buttons. </summary>
            PointerButtons State;
        };

        /// <summary> An event structure containing information about user interactions with keyboard keys. </summary>
        /// <remarks>
        ///     This event structure gets dispatched every time a keyboard key is either pressed or released while the 
        ///     <see cref="Window3D"/> rendering window has input focus. 
        /// </remarks>
        struct KeyboardEvent
        {
            ubyte Code;
            /// <summary> The specific keyboard key that has been either pressed or released. </summary>
            const KeyboardKeys& Key;
            /// <summary> The current state of all keyboard keys. </summary>
            const KeyboardKeys& State;
        };

    }
}
