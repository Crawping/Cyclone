/* CHANGELOG
 * Written by Josh Grooms on 20160923
 */

#pragma once
#include "Enumerator.h"
#include "PlatformAPI.h"



namespace Cyclone
{
    namespace { using namespace Cyclone::Utilities; }

    namespace Platform
    {
        struct InputControls : public Flag<InputControls>
        {
            enum Controls : int
            {
                Nothing     = 0,
                /* ALT - Represents the left or right 'Alt' keyboard key.
                 * 
                 *      'Alt' is equivalent to the 'Mod1Mask' X library key on my home desktop PC.
                 */
                Alt         = (1 << 0),
                /* CAPSLOCK - Represents the 'CapsLock' keyboard toggle.
                 * 
                 *      'CapsLock' is equivalent to the 'LockMask' X library key on my home desktop PC.
                 */
                CapsLock    = (1 << 1),
                /* CTRL - Represents the left or right 'Ctrl' keyboard key.
                 * 
                 *      'Ctrl' is equivalent to the 'ControlMask' X library key on my home desktop PC.
                 */
                Ctrl        = (1 << 2),
                Hyper       = (1 << 3),
                Meta        = (1 << 4),
                /* NUMLOCK - Represents the 'NumLock' keyboard toggle.
                 * 
                 *      'NumLock' is equivalent to the 'Mod2Mask' X library key on my home desktop PC.
                 */
                NumLock     = (1 << 5),
                /* SHIFT - Represents the left or right 'Shift' keyboard key.
                 * 
                 *      'Shift' is equivalent to the 'ShiftMask' X library key on my home desktop PC.
                 */
                Shift       = (1 << 6),
                /* SUPER - Represents the 'super' keyboard key, which is typically the 'Windows' key.
                 * 
                 *      Super is equivalent to the 'Mod4Mask' X library key mask on my home PC.
                 */
                Super       = (1 << 7),
                Switch      = (1 << 8),  
                /* BUTTON001 - Represents the primary or left mouse button. */
                Button001   = (1 << 9),
                /* BUTTON002 - Represents the middle mouse button, which is typically the scroll wheel. */
                Button002   = (1 << 10),
                /* BUTTON003 - Represents the secondary or right mouse button. */
                Button003   = (1 << 11),
                /* BUTTON004 - Represents the mouse scroll wheel being moved in the upward direction. */
                Button004   = (1 << 12),
                /* BUTTON005 - Represents the mouse scroll wheel being moved in the downward direction. */
                Button005   = (1 << 13),
                Button006   = (1 << 14),
                Button007   = (1 << 15),
                Button008   = (1 << 16),
                Button009   = (1 << 17),
                Button010   = (1 << 18),
                Button011   = (1 << 19),
                Button012   = (1 << 20),
                Button013   = (1 << 21),
                Button014   = (1 << 22),
                Button015   = (1 << 23),
                Button016   = (1 << 24),
                Button017   = (1 << 25),
                Button018   = (1 << 26),
                Button019   = (1 << 27),
                Button020   = (1 << 28),
                Movement    = (1 << 29),
            };
    
    
            /** CONSTRUCTORS **/
            InputControls(enum Controls c = Nothing) : Flag((int)c) { }
            InputControls(int c) : Flag(c) { }
    
    
    
            /** UTILITIES **/
            /* REPORT - Creates a string containing all of the recognized values that have been set on this flag. */
            PlatformAPI string Report() const;
            /* TOSTRING - Converts any of the above control enumerators into an equivalent string representation. */
            PlatformAPI string ToString() const;
    
            InputControls& operator &=(const InputControls& other) { Value &= other.Value; return *this; }
            InputControls& operator |=(const InputControls& other) { Value |= other.Value; return *this; }
        };
    }
}