/* CHANGELOG
 * Written by Josh Grooms on 20150905
 */

#pragma once
#include "Vector2.h"



//namespace Cyclone::Utilities
//{
namespace Cyclone
{
    namespace Utilities
    {

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
            /// <summary> The x-coordinate of the vector. </summary>
            float X;
            /// <summary> The y-coordiante of the vector. </summary>
            float Y;
            /// <summary> The z-coordinate of the vector. </summary>
            float Z;



            /** CONSTRUCTORS **/
            /// <summary> Constructs a 3-element vector pointing to the origin (0, 0, 0). </summary>
            constexpr Vector3()                                     : X(0), Y(0), Z(0) { }
            /// <summary> Constructs a 3-element vector pointing to uniform coordinates. </summary>
            /// <param name="v"> A single number to be copied to each of the three vector elements. </param>
            constexpr Vector3(float v)                              : X(v), Y(v), Z(v) { }
            /// <summary> Constructs a 3-element vector by appending a z-coordinate to a 2-element vector. </summary>
            /// <param name="v"> An existing 2-element vector of values. </param>
            /// <param name="z">
            ///     The z-coordinate to be appended to the inputted vector <paramref name="v"/>.
            ///     DEFAULT: 0.0f
            /// </param>
            constexpr Vector3(const Vector2& v, float z = 0.0f)     : X(v.X), Y(v.Y), Z(z) { }
            /// <summary> Constructs a 3-element vector pointing to the specified coordinates. </summary>
            /// <param name="x"> The desired x-coordinate of the vector. </param>
            /// <param name="y"> The desired y-coordinate of the vector. </param>
            /// <param name="z"> The desired z-coordinate of the vector. </param>
            constexpr Vector3(float x, float y, float z)            : X(x), Y(y), Z(z) { }



            /** UTILITIES **/
            /// <summary> Moves the vector relative to its current position. </summary>
            /// <returns> A reference to the modified vector, which is useful for chaining operations together. </returns>
            /// <param name="x"> The amount by which the x-coordinate of this vector should move. </param>
            /// <param name="y"> The amount by which the y-coordinate of this vector should move. </param>
            /// <param name="z"> The amount by which the z-coordinate of this vector should move. </param>
            /// <remarks>
            ///     This method moves a vector relative to the point that it stores. Thus, for example, if a vector points 
            ///     to the position (x0, y0, z0) and is translated by an amount (x1, y1, z1), its position at the end of 
            ///     this method call will be (x0 + x1, y0 + y1, z0 + z1).
            /// </remarks>
            Vector3& Translate(float x, float y, float z)       { X += x; Y += y; Z += z; return *this; }
            /// <summary> Moves the vector relative to its current position. </summary>
            /// <returns> A reference to the modified vector, which is useful for chaining operations together. </returns>
            /// <param name="t"> The (x, y, z) amounts by which this vector should move. </param>
            /// <remarks>
            ///     This method moves a vector relative to the point that it stores. Thus, for example, if a vector points 
            ///     to the position (x0, y0, z0) and is translated by an amount (x1, y1, z1), its position at the end of 
            ///     this method call will be (x0 + x1, y0 + y1, z0 + z1).
            /// </remarks>
            Vector3& Translate(const Vector3& t)                { return Translate(t.X, t.Y, t.Z); }



            /** OPERATORS **/
            /// <summary> Converts the object from a 3-element vector into a 2-element one by ignoring the z-coordinate. </summary>
            /// <returns> A new 2-element vector containing the (x, y) coordinates from the original 3-element one. </returns>
            constexpr explicit operator Vector2()               const { return Vector2(X, Y); }

            float& operator ()(int index)                             { return index ? (index == 1 ? Y : Z) : X; }
            constexpr float operator ()(int index)              const { return index ? (index == 1 ? Y : Z) : X; }

            /// <summary> Determines whether one vector's elements are equivalent to another's. </summary>
            /// <param name="v"> Another vector against which equality testing will occur. </param>
            /// <returns> A Boolean <c>true</c> if both vectors contain equivalent values, or <c>false</c> otherwise. </returns>
            constexpr bool operator ==(const Vector3& v)        const { return X == v.X && Y == v.Y && Z == v.Z; }
            /// <summary> Determines whether one vector's elements are not equivalent to another's. </summary>
            /// <param name="v"> Another vector against which inequality testing will occur. </param>
            /// <returns> A Boolean <c>true</c> if both vectors contain different values, or <c>false</c> otherwise. </returns>
            constexpr bool operator !=(const Vector3& v)        const { return !(*this == v); }

            constexpr Vector3 operator +(float v)               const { return Vector3(X + v, Y + v, Z + v); }
            constexpr Vector3 operator +(const Vector3& v)      const { return Vector3(X + v.X, Y + v.Y, Z + v.Z); }
    
            constexpr Vector3 operator /(float v)               const { return Vector3(X / v, Y / v, Z / v); }
            constexpr Vector3 operator /(const Vector3& v)      const { return Vector3(X / v.X, Y / v.Y, Z / v.Z); }

            constexpr Vector3 operator *(float v)               const { return Vector3(X * v, Y * v, Z * v); }
            constexpr Vector3 operator *(const Vector3& v)      const { return Vector3(X * v.X, Y * v.Y, Z * v.Z); }

            constexpr Vector3 operator -()                      const { return Vector3(-X, -Y, -Z); }
            constexpr Vector3 operator -(float v)               const { return Vector3(X - v, Y - v, Z - v); }
            constexpr Vector3 operator -(const Vector3& v)      const { return Vector3(X - v.X, Y - v.Y, Z - v.Z); }

            /// <summary> Moves this vector relative to its current position. </summary>
            /// <returns> A reference to the modified vector, which is useful for chaining operations together. </returns>
            /// <param name="v"> The uniform amount by which the (x, y, z) coordinates of this vector should move. </param>
            /// <remarks>
            ///     This method is effectively a shorthand for invoking the <see cref="Translate"/> method.
            /// </remarks>
            Vector3& operator +=(float v)                             { return Translate(v, v, v); }
            /// <summary> Moves this vector relative to its current position. </summary>
            /// <returns> A reference to the modified vector, which is useful for chaining operations together. </returns>
            /// <param name="v"> The (x, y, z) amounts by which this vector should move. </param>
            /// <remarks>
            ///     This method is effectively a shorthand for invoking the <see cref="Translate"/> method.
            /// </remarks>
            Vector3& operator +=(const Vector3& v)                    { return Translate(v); }

            Vector3& operator -=(float v)                             { return Translate(-v, -v, -v); }
            Vector3& operator -=(const Vector3& v)                    { return Translate(-v); }

            Vector3& operator *=(const Vector3& v)                    { X *= v.X; Y *= v.Y; Z *= v.Z; return *this; }
        };
    }
}
    