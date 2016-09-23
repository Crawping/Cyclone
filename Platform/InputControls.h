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
                /// <summary> The left or right alt keyboard key. </summary>
                /// <remarks>
                ///     In Linux, the alt key is equivalent to <see cref="Mod1Mask"/> on my home desktop PC.
                /// </remarks>
                Alt         = (1 << 0),
                /// <summary> The caps lock keyboard key toggle. </summary>
                /// <remarks>
                ///     In Linux, the caps lock key is equivalent to <see cref="LockMask"/> on my home desktop PC.
                /// </remarks>
                CapsLock    = (1 << 1),
                /// <summary> The left or right ctrl keyboard key. </summary>
                /// <remarks>
                ///     In Linux, the ctrl key is equivalent to <see cref="ControlMask"/> on my home desktop PC.
                /// </remarks>
                Ctrl        = (1 << 2),
                Hyper       = (1 << 3),
                Meta        = (1 << 4),
                /// <summary> The numlock keyboard key toggle. </summary>
                /// <remarks>
                ///     In Linux, the numlock key is equivalent to <see cref="Mod2Mask"/> on my home desktop PC.
                /// </remarks>
                NumLock     = (1 << 5),
                /// <summary> The left or right shift keyboard key. </summary>
                /// <remarks>
                ///     In Linux, the shift key is equivalent to <see cref="ShiftMask"/> on my home desktop PC.
                /// </remarks>
                Shift       = (1 << 6),
                /// <summary> The super keyboard key, which is typically the Windows key. </summary>
                /// <remarks>
                ///     In Linux, the super key is equivalent to <see cref="Mod4Mask"/> on my home desktop PC.
                /// </remarks>
                Super       = (1 << 7),
                Switch      = (1 << 8),  
                /// <summary> The primary or left mouse button. </summary>
                Button001   = (1 << 9),
                /// <summary> The middle mouse button, which is typically the scroll wheel. </summary>
                Button002   = (1 << 10),
                /// <summary> The secondary or right mouse button. </summary>
                Button003   = (1 << 11),
                /// <summary> The scroll wheel rolled in the upward direction. </summary>
                Button004   = (1 << 12),
                /// <summary> The scroll wheel rolled in the downward direction. </summary>
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
            /// <summary> Creates a human-readable string containing all of the recognized values that have been set on this flag. </summary>
            PlatformAPI string Report() const;
            /// <summary> Converts a single control enumerator into an equivalent string representation. </summary>
            PlatformAPI string ToString() const;
    
            InputControls& operator &=(const InputControls& other) { Value &= other.Value; return *this; }
            InputControls& operator |=(const InputControls& other) { Value |= other.Value; return *this; }
        };
    }
}