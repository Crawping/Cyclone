/* CHANGELOG
 * Written by Josh Grooms on 20150910
 */

#pragma once
#include "TypeDefinitions.h"
#include "UtilitiesAPI.h"



namespace Cyclone
{
    namespace Utilities
    {

        struct UtilitiesAPI Vector2
        {

            /** STATIC DATA **/
            /// <summary> A vector whose value is (1, 1, 1). </summary>
            const static Vector2 One;
            /// <summary> A unit vector in the x direction (1, 0). </summary>
            const static Vector2 UnitX;
            /// <summary> A unit vector in the y direction (0, 1).  </summary>
            const static Vector2 UnitY;
            /// <summary> A vector of zero length pointing to the origin (0, 0). </summary>
            const static Vector2 Zero;



            /** DATA **/
            /// <summary> The x-coordinate of the vector. </summary>
            float X;
            /// <summary> The y-coordinate of the vector. </summary>
            float Y;



            /** CONSTRUCTORS **/
            /// <summary> Constructs a 2-element vector pointing to the origin (0, 0). </summary>
            constexpr Vector2()                 : X(0), Y(0) { }
            /// <summary> Constructs a 2-element vector pointing to uniform coordinates. /summary>
            /// <param name="v"> A single number to be copied to each of the two vector elements. </param>
            constexpr Vector2(float v)          : X(v), Y(v) { }
            /// <summary> Constructs a 2-element vector pointing to the specified coordinates. </summary>
            /// <param name="x"> The desired x-coordinate of the vector. </param>
            /// <param name="y"> The desired y-coordinate of the vector. </param>
            constexpr Vector2(float x, float y) : X(x), Y(y) { }



            /** UTILITIES **/
            string ToString() const;
            /// <summary> Moves the vector relative to its current position. </summary>
            /// <param name="x"> The amount by which the x-coordinate of the vector should move. </param>
            /// <param name="y"> The amount by which the y-coordinate of the vector should move. </param>
            Vector2& Translate(float x, float y) { X += x; Y += y; return *this; }
            /// <summary> Moves the vector relative to its current position. </summary>
            /// <param name="v"> The (x, y) amounts by which the vector should move. </param>
            Vector2& Translate(const Vector2& v) { X += v.X; Y += v.Y; return *this; }



            /** OPERATORS **/
            float& operator ()(int index)                             { return index ? Y : X; }
            constexpr float operator ()(int index)              const { return index ? Y : X; }

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
}
