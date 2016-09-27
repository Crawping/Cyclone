/* CHANGELOG
 * Written by Josh Grooms on 20151126
 */

#pragma once
#include "Enumerator.h"
#include "PlatformAPI.h"
#include <bitset>



namespace Cyclone
{
    namespace { using namespace Cyclone::Utilities; }

    namespace Platform
    {
        struct PointerButtons : public Flag<PointerButtons>
        {
            enum Controls : int
            {
                Nothing     = 0,
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
            PointerButtons(enum Controls c = Nothing) : Flag((int)c) { }
            PointerButtons(int c) : Flag(c) { }



            /** UTILITIES **/
            /// <summary> Creates a human-readable string containing all of the recognized values that have been set on this flag. </summary>
            PlatformAPI string Report() const;
            /// <summary> Converts a single control enumerator into an equivalent string representation. </summary>
            PlatformAPI string ToString() const;

            PointerButtons& operator &=(const PointerButtons& other) { Value &= other.Value; return *this; }
            PointerButtons& operator |=(const PointerButtons& other) { Value |= other.Value; return *this; }
        };



        struct KeyboardKeys
        {

            public:
                enum Keys
                {
                    Nothing = 0,

                    Escape,

                    F1,
                    F2,
                    F3,
                    F4,
                    F5,
                    F6,
                    F7,
                    F8,
                    F9,
                    F10,
                    F11,
                    F12,

                    Zero,
                    One,
                    Two,
                    Three,
                    Four,
                    Five,
                    Six,
                    Seven,
                    Eight,
                    Nine,

                    A,
                    B,
                    C,
                    D,
                    E,
                    F,
                    G,
                    H,
                    I,
                    J,
                    K,
                    L,
                    M,
                    N,
                    O,
                    P,
                    Q,
                    R,
                    S,
                    T,
                    U,
                    V,
                    W,
                    X,
                    Y,
                    Z,

                    Apostrophe,
                    BackTick,
                    BracketOpen,
                    BracketClose,
                    BackSlash,
                    Comma,
                    Dash,
                    Equals,
                    ForwardSlash,
                    Period,
                    Semicolon,

                    Backspace,
                    Enter,
                    Space,
                    Tab,

                    /// <summary> The left or right alt keyboard key. </summary>
                    /// <remarks>
                    ///     In Linux, the alt key is equivalent to <see cref="Mod1Mask"/> on my home desktop PC.
                    /// </remarks>
                    Alt,
                    /// <summary> The caps lock keyboard key toggle. </summary>
                    /// <remarks>
                    ///     In Linux, the caps lock key is equivalent to <see cref="LockMask"/> on my home desktop PC.
                    /// </remarks>
                    CapsLock,
                    /// <summary> The left or right ctrl keyboard key. </summary>
                    /// <remarks>
                    ///     In Linux, the ctrl key is equivalent to <see cref="ControlMask"/> on my home desktop PC.
                    /// </remarks>
                    Control,
                    /// <summary> The left or right shift keyboard key. </summary>
                    /// <remarks>
                    ///     In Linux, the shift key is equivalent to <see cref="ShiftMask"/> on my home desktop PC.
                    /// </remarks>
                    Shift,
                    /// <summary> The super keyboard key, which is typically the Windows key. </summary>
                    /// <remarks>
                    ///     In Linux, the super key is equivalent to <see cref="Mod4Mask"/> on my home desktop PC.
                    /// </remarks>
                    Super,

                    Delete,
                    Down,
                    End,
                    Home,
                    Insert,
                    Left,
                    Menu,
                    PageDown,
                    PageUp,
                    Pause,
                    PrintScreen,
                    Right,
                    ScrollLock,
                    Up,

                    AsteriskKP,
                    DashKP,
                    EnterKP,
                    ForwardSlashKP,
                    /// <summary> The numlock keyboard key toggle. </summary>
                    /// <remarks>
                    ///     In Linux, the numlock key is equivalent to <see cref="Mod2Mask"/> on my home desktop PC.
                    /// </remarks>
                    NumLock,
                    PeriodKP,
                    PlusKP,

                    KP0,
                    KP1,
                    KP2,
                    KP3,
                    KP4,
                    KP5,
                    KP6,
                    KP7,
                    KP8,
                    KP9,
                };

                /// <summary> Gets the number of keys currently pressed on the keyboard. </summary>
                uint Count() const { return State.count(); }



                /** CONSTRUCTOR **/
                PlatformAPI KeyboardKeys(enum Keys k = Nothing);



                /** UTILITIES **/
                PlatformAPI bool IsPressed(enum Keys k) const;
                PlatformAPI bool IsPressed(const KeyboardKeys& k) const;
                PlatformAPI KeyboardKeys& Press(enum Keys k);
                PlatformAPI KeyboardKeys& Press(const KeyboardKeys& k);
                PlatformAPI KeyboardKeys& Release(enum Keys k);
                PlatformAPI KeyboardKeys& Release(const KeyboardKeys& k);

                PlatformAPI string Report() const;
                PlatformAPI string ToString() const;


                /** OPERATORS **/
                PlatformAPI bool operator ==(const KeyboardKeys& other) const;
                bool operator !=(const KeyboardKeys& other) const { return !(*this == other); }


            private:

                std::bitset<128> State;

        };
    }
}
