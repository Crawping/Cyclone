/* CHANGELOG
 * Written by Josh Grooms on 20150907
 */

#pragma once
#include "TypeDefinitions.h"
#include "UtilitiesAPI.h"



/* COLOR4 - A data structure representing a 32-bit RGBA color value.
 *
 *      Color4 is a tightly packed data structure laid out in RGBA format. Individual channel values should take on
 *      single-precision (i.e. float) values within the closed interval [0.0f, 1.0f].
 */
struct UtilitiesAPI Color4
{

    /** CONSTANT DATA **/
    const static Color4 Black;
    const static Color4 Blue;
    const static Color4 Cyan;
    const static Color4 Green;
    const static Color4 Magenta;
    const static Color4 Red;
    const static Color4 Transparent;
    const static Color4 White;
    const static Color4 Yellow;



    /// <summary> The red channel value of the color. </summary>
    float R;
	/// <summary> The green channel value of the color. </summary>
    float G;
	/// <summary> The blue channel value of the color. </summary>
    float B;
	/// <summary> The alpha channel value of the color. </summary>
    float A;



    /** CONSTRUCTORS **/
	/// <summary> Constructs an opaque black RGBA color vector. </summary>
    constexpr Color4()                                          : R(0), G(0), B(0), A(1) { }
	/// <summary> Constructs an opaque gray RGBA color vector. </summary>
    constexpr Color4(float gray)                                : R(gray), G(gray), B(gray), A(1) { }
	/// <summary> Constructs an RGBA color vector. </summary>
    constexpr Color4(float r, float g, float b, float a = 1.0f) : R(r), G(g), B(b), A(a) { }



    /** UTILITIES **/
	/// <summary> Creates a random opaque color with channel values drawn from a uniform distribution. </summary>
    static Color4 Random();
	/// <summary> Converts this color structure into an array of four float values ordered as RGBA. </summary>
    float* ToArray()                                              { return (float*)this; }
	/// <summary> Converts this color structure into an array of four float values ordered as RGBA. </summary>
    constexpr const float* ToArray()                        const { return (const float*)this; }
	/// <summary> Converts this color structure into a packed 32-bit integer containing the RGBA values. </summary>
    constexpr int ToInt()                                   const;
	/// <summary> Converts this color structure into a string containing the four RGBA channel values. </summary>
    string ToString()                                       const;



    /** OPERATORS **/
	/// <summary> Determines if two color data structures have equivalent channel values. </summary>
    constexpr bool operator ==(const Color4& other)         const
    {
        return R == other.R && G == other.G && B == other.B && A == other.A;
    }
    /// <summary> Determines if two color data structures have unequal channel values. </summary>
    constexpr bool operator !=(const Color4& other)         const { return !(*this == other); }

};
