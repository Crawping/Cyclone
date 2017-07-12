/* CHANGELOG
 * Written by Josh Grooms on 20160608
 */

#pragma once
#include "Vector2.h"
#include "Vector3.h"



namespace Cyclone
{
    namespace Utilities
    {
        struct UtilitiesAPI Vector4
        {

            /** STATIC DATA **/
            /// <summary> A vector whose value is (1, 1, 1, 1). </summary>
            const static Vector4 One;
            /// <summary> A unit vector in the x direction (1, 0, 0, 0). </summary>
            const static Vector4 UnitX;
            /// <summary> A unit vector in the y direction (0, 1, 0, 0). </summary>
            const static Vector4 UnitY;
            /// <summary> A unit vector in the z direction (0, 0, 1, 0). </summary>
            const static Vector4 UnitZ;
            /// <summary> A unit vector in the w direction (0, 0, 0, 1). </summary>
            const static Vector4 UnitW;
            /// <summary> A vector of zero length pointing to the origin (0, 0, 0, 0). </summary>
            const static Vector4 Zero;



            /** DATA **/
            /// <summary> The x-coordinate of the vector. </summary>
            float X;
            /// <summary> The y-coordinate of the vector. </summary>
            float Y;
            /// <summary> The z-coordinate of the vector. </summary>
            float Z;
            /// <summary> The w-coordinate of the vector. </summary>
            float W;



            /** CONSTRUCTORS **/
            /// <summary> Constructs a four-element vector pointing to the origin (0, 0, 0, 0). </summary>
            constexpr Vector4(): X(0), Y(0), Z(0), W(0) { }
            /// <summary> Constructs a four-element vector pointing to uniform coordinates. </summary>
            /// <param name="v"> A single number to be copied to each of the four vector elements. </param>
            constexpr Vector4(float v) : X(v), Y(v), Z(v), W(v) { }
            /// <summary> Constructs a four-element vector by appending a w-coordinate to a three-element vector. </summary>
            /// <param name="v"> An existing three-element vector of values. </param>
            /// <param name="w"> The desired w-coordinate of the vector. </param>
            constexpr Vector4(const Vector3& v, float w = 0.0f) : X(v.X), Y(v.Y), Z(v.Z), W(w) { }
            /// <summary> Constructs a four-element vector by appending a z- and w-coordinate to a two-element vector. </summary>
            /// <param name="v"> An existing two-element vector of values. </param>
            /// <param name="z"> The desired z-coordinate of the vector. </param>
            /// <param name="w"> The desired w-coordinate of the vector. </param>
            constexpr Vector4(const Vector2& v, float z = 0.0f, float w = 0.0f) : X(v.X), Y(v.Y), Z(z), W(w) { }
            /// <summary> Constructs a four-element vector pointing to the specified coordinates. </summary>
            /// <param name="x"> The desired x-coordinate of the vector. </param>
            /// <param name="y"> The desired y-coordinate of the vector. </param>
            /// <param name="z"> The desired z-coordinate of the vector. </param>
            /// <param name="w"> The desired w-coordinate of the vector. </param>
            constexpr Vector4(float x, float y, float z, float w): X(x), Y(y), Z(z), W(w) { }



            /** UTILITIES **/
            /// <summary> Moves the vector relative to its current position. </summary>
            /// <returns> A reference to the modified vector, which is useful for chaining operations together. </returns>
            /// <param name="x"> The amount by which the x-coordinate of this vector should move. </param>
            /// <param name="y"> The amount by which the y-coordinate of this vector should move. </param>
            /// <param name="z"> The amount by which the z-coordinate of this vector should move. </param>
            /// <param name="w"> The amount by which the w-coordinate of this vector should move. </param>
            /// <remarks>
            ///     This method moves a vector relative to the point that it stores. Thus, for example, if a vector points 
            ///     to the position (x0, y0, z0, w0) and is translated by an amount (x1, y1, z1, w1), its position at the 
            ///     end of this method call will be (x0 + x1, y0 + y1, z0 + z1, w0 + w1).
            /// </remarks>
            Vector4& Translate(float x, float y, float z, float w)
            {
                X += x; Y += y;
                Z += z; W += w;
                return *this;
            }
            /// <summary> Moves the vector relative to its current position. </summary>
            /// <returns> A reference to the modified vector, which is useful for chaining operations together. </returns>
            /// <param name="t"> The (x, y, z, w) amounts by which this vector should move. </param>
            /// <remarks>
            ///     This method moves a vector relative to the point that it stores. Thus, for example, if a vector points 
            ///     to the position (x0, y0, z0, w0) and is translated by an amount (x1, y1, z1, w1), its position at the 
            ///     end of this method call will be (x0 + x1, y0 + y1, z0 + z1, w0 + w1).
            /// </remarks>
            Vector4& Translate(const Vector4& t) { return Translate(t.X, t.Y, t.Z, t.W); }



            /** OPERATORS **/
            /// <summary> Converts the object from a four-element vector into a two-element one by ignoring the (z, w) coordinates. </summary>
            /// <returns> A new two-element vector containing the (x, y) coordinates from the original. </returns>
            constexpr explicit operator Vector2()                   const { return Vector2(X, Y); }
            /// <summary> Converts the object from a four-element vector into a three-element one by ignoring the w-coordinate. </summary>
            /// <returns> A new two-element vector containing the (x, y, z) coordinates from the original. </returns>
            constexpr explicit operator Vector3()                   const { return Vector3(X, Y, Z); }

            /// <summary> Determines whether one vector's elements are equivalent to another's. </summary>
            /// <param name="v"> Another vector against which equality testing will occur. </param>
            /// <returns> A Boolean <c>true</c> if both vectors contain equivalent values, or <c>false</c> otherwise. </returns>
            constexpr bool operator ==(const Vector4& v)            const { return X == v.X && Y == v.Y && Z == v.Z && W == v.W; }
            /// <summary> Determines whether one vector's elements are not equivalent to another's. </summary>
            /// <param name="v"> Another vector against which inequality testing will occur. </param>
            /// <returns> A Boolean <c>true</c> if both vectors contain different values, or <c>false</c> otherwise. </returns>
            constexpr bool operator !=(const Vector4& v)            const { return !(*this == v); }

            /// <summary> Divides each element of the vector by a single value. </summary>
            Vector4& operator /=(float v)
            {
                X /= v; Y /= v;
                Z /= v; W /= v;
                return *this;
            }

        };
    }
}