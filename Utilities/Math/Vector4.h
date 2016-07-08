/* CHANGELOG
 * Written by Josh Grooms on 20160608
 */

#pragma once
#include "Vector2.h"
#include "Vector3.h"



namespace Cyclone::Utilities
{
    struct UtilitiesAPI Vector4
    {

        /** STATIC DATA **/
        const static Vector4 One;
        const static Vector4 UnitX;
        const static Vector4 UnitY;
        const static Vector4 UnitZ;
        const static Vector4 UnitW;
        const static Vector4 Zero;



        /** DATA **/

        float X;
        float Y;
        float Z;
        float W;



        /** CONSTRUCTORS **/
        constexpr Vector4()                                                     : X(0), Y(0), Z(0), W(0) { }
        constexpr Vector4(float v)                                              : X(v), Y(v), Z(v), W(v) { }
        constexpr Vector4(const Vector3& v, float w = 0.0f)                     : X(v.X), Y(v.Y), Z(v.Z), W(w) { }
        constexpr Vector4(const Vector2& v, float z = 0.0f, float w = 0.0f)     : X(v.X), Y(v.Y), Z(z), W(w) { }
        constexpr Vector4(float x, float y, float z, float w)                   : X(x), Y(y), Z(z), W(w) { }



        /** UTILITIES **/
        Vector4& Translate(float x, float y, float z, float w)        { X += x; Y += y; Z += z; W += w; return *this; }
        Vector4& Translate(const Vector4& t)                          { return Translate(t.X, t.Y, t.Z, t.W); }



        /** OPERATORS **/
        constexpr explicit operator Vector2()                   const { return Vector2(X, Y); }
        constexpr explicit operator Vector3()                   const { return Vector3(X, Y, Z); }

        constexpr bool operator ==(const Vector4& v)            const { return X == v.X && Y == v.Y && Z == v.Z && W == v.W; }
        constexpr bool operator !=(const Vector4& v)            const { return !(*this == v); }

    };
}