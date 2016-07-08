/* CHANGELOG
 * Written by Josh Grooms on 20150910
 */

#pragma once
#include "TypeDefinitions.h"
#include "UtilitiesAPI.h"



namespace Cyclone::Utilities
{
    struct UtilitiesAPI Vector2
    {

        /** STATIC DATA **/
        /* ONE - A vector whose value is (1, 1, 1). */
        const static Vector2 One;
        /* UNITX - A unit vector in the x direction (1, 0). */
        const static Vector2 UnitX;
        /* UNITY - A unit vector in the y direction (0, 1). */
        const static Vector2 UnitY;
        /* ZERO - A vector of zero length pointing to the origin (0, 0). */
        const static Vector2 Zero;



        /** DATA **/
        /* X - The x-coordinate of the vector. */
        float X;
        /* Y - The y-coordinate of the vector. */
        float Y;



        /** CONSTRUCTORS **/
        /* VECTOR2 - Constructs a 2-element vector pointing to the origin (0, 0). */
        constexpr Vector2()                 : X(0), Y(0) { }
        /* VECTOR2 - Constructs a 2-element vector pointing to uniform coordinates. */
        constexpr Vector2(float v)          : X(v), Y(v) { }
        /* VECTOR2 - Constructs a 2-element vector pointing to the specified coordinates. */
        constexpr Vector2(float x, float y) : X(x), Y(y) { }



        /** UTILITIES **/
        /* TRANSLATE - Moves the vector relative to its current position. */
        Vector2& Translate(float x, float y) { X += x; Y += y; return *this; }
        /* TRANSLATE - Moves the vector relative to its current position. */
        Vector2& Translate(const Vector2& v) { X += v.X; Y += v.Y; return *this; }



        /** OPERATORS **/
        float& operator [](int index)                             { return index ? Y : X; }
        constexpr float operator [](int index)              const { return index ? Y : X; }

        constexpr bool operator ==(const Vector2& other)    const { return X == other.X && Y == other.Y; }
        constexpr bool operator !=(const Vector2& other)    const { return !(*this == other); }

        constexpr Vector2 operator +(float v)               const { return Vector2(X + v, Y + v); }
        constexpr Vector2 operator +(const Vector2& v)      const { return Vector2(X + v.X, Y + v.Y); }

        constexpr Vector2 operator /(float v)               const { return Vector2(X / v, Y / v); }
        constexpr Vector2 operator /(const Vector2& v)      const { return Vector2(X / v.X, Y / v.Y); }

        constexpr Vector2 operator *(float v)               const { return Vector2(X * v, Y * v); }
        constexpr Vector2 operator *(const Vector2& v)      const { return Vector2(X * v.X, Y * v.Y); }

        constexpr Vector2 operator -()                      const { return Vector2(-X, -Y); }
        constexpr Vector2 operator -(float v)               const { return *this + (-v); }
        constexpr Vector2 operator -(const Vector2& v)      const { return *this + (-v); }

        Vector2& operator +=(float v)                             { return Translate(v, v); }
        Vector2& operator +=(const Vector2& v)                    { return Translate(v); }

        Vector2& operator /=(float v)                             { X /= v; Y /= v; return *this; }
        Vector2& operator /=(const Vector2& v)                    { X /= v.X; Y /= v.Y; return *this; }

        Vector2& operator *=(float v)                             { X *= v; Y *= v; return *this; }
        Vector2& operator *=(const Vector2& v)                    { X *= v.X; Y *= v.Y; return *this; }

        Vector2& operator -=(float v)                             { return Translate(-v, -v); }
        Vector2& operator -=(const Vector2& v)                    { return Translate(-v); }

    };



    /** OPERATORS LED BY SINGLE NUMBERS **/
    constexpr Vector2 operator +(float left, const Vector2& right) { return right + left; }
    constexpr Vector2 operator /(float left, const Vector2& right) { return Vector2(left / right.X, left / right.Y); }
    constexpr Vector2 operator *(float left, const Vector2& right) { return right * left; }
    constexpr Vector2 operator -(float left, const Vector2& right) { return -right + left; }

}