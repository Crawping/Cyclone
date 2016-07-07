/* CHANGELOG
 * Written by Josh Grooms on 20150905
 */

#pragma once
#include "Vector2.h"



struct UtilitiesAPI Vector3
{
    

    /** STATIC DATA **/
    /// <summary> A vector whose value is (1, 1, 1). </summary>
    const static Vector3 One;
    /// <summary> A unit vector in the x direction (1, 0, 0). </summary>
    const static Vector3 UnitX;
    /// <summary> A unit vector in the y direction (0, 1, 0). </summary>
    const static Vector3 UnitY;
    /// <summary> A unit vector in the z direction (0, 0, 1). </summary>
    const static Vector3 UnitZ;
    /// <summary> A vector of zero length pointing to the origin (0, 0, 0). </summary>
    const static Vector3 Zero;



    /** DATA **/
    /* X - The x-coordinate of the vector. */
    float X;
    /* Y - The y-coordiante of the vector. */
    float Y;
    /* Z - The z-coordinate of the vector. */
    float Z;



    /** CONSTRUCTORS **/
    /* VECTOR3 - Constructs a 3-element vector pointing to the origin (0, 0, 0). */
    constexpr Vector3()                                     : X(0), Y(0), Z(0) { }
    /* VECTOR3 - Constructs a 3-element vector pointing to uniform coordinates. */
    constexpr Vector3(float v)                              : X(v), Y(v), Z(v) { }

    constexpr Vector3(const Vector2& v, float z = 0.0f)     : X(v.X), Y(v.Y), Z(z) { }
    /* VECTOR3 - Constructs a 3-element vector pointing to the specified coordinates. */
    constexpr Vector3(float x, float y, float z)            : X(x), Y(y), Z(z) { }



    /** UTILITIES **/
    /* TRANSLATE - Moves the vector relative to its current position. */
    Vector3& Translate(float x, float y, float z)       { X += x; Y += y; Z += z; return *this; }
    /* TRANSLATE - Moves the vector relative to its current position. */
    Vector3& Translate(const Vector3& t)                { return Translate(t.X, t.Y, t.Z); }



    /** OPERATORS **/

    constexpr explicit operator Vector2()               const { return Vector2(X, Y); }

    float& operator [](int index)                             { return index ? (index == 1 ? Y : Z) : X; }
    constexpr float operator [](int index)              const { return index ? (index == 1 ? Y : Z) : X; }

    constexpr bool operator ==(const Vector3& v)        const { return X == v.X && Y == v.Y && Z == v.Z; }
    constexpr bool operator !=(const Vector3& v)        const { return !(*this == v); }

    constexpr Vector3 operator +(const Vector3& v)      const { return Vector3(X + v.X, Y + v.Y, Z + v.Z); }
    constexpr Vector3 operator +(float v)               const { return Vector3(X + v, Y + v, Z + v); }

    constexpr Vector3 operator /(float v)               const { return Vector3(X / v, Y / v, Z / v); }
    constexpr Vector3 operator /(const Vector3& v)      const { return Vector3(X / v.X, Y / v.Y, Z / v.Z); }

    constexpr Vector3 operator *(float v)               const { return Vector3(X * v, Y * v, Z * v); }
    constexpr Vector3 operator *(const Vector3& v)      const { return Vector3(X * v.X, Y * v.Y, Z * v.Z); }
    constexpr Vector3 operator -()                      const { return Vector3(-X, -Y, -Z); }
    constexpr Vector3 operator -(float v)               const { return Vector3(X - v, Y - v, Z - v); }

    Vector3& operator +=(float v)                             { return Translate(v, v, v); }
    Vector3& operator +=(const Vector3& v)                    { return Translate(v); }

    Vector3& operator -=(float v)                             { return Translate(-v, -v, -v); }
    Vector3& operator -=(const Vector3& v)                    { return Translate(-v); }
};
