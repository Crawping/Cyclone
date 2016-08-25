/* CHANGELOG
 * Written by Josh Grooms on 20150907
 */

#pragma once
#include "Math/Vector2.h"
#include "Math/Vector3.h"



namespace Cyclone
{
    namespace Utilities
    {
        struct Vertex
        {

            /** DATA **/
            /// <summary> The position of the vertex in model space. </summary>
            Vector3 Position;
	        /// <summary> The texture coordinates associated with the vertex. </summary>
            Vector2 UV;



            /** PROPERTIES **/
	        /// <summary> Gets the position of the vertex along the texture u-axis. </summary>
            constexpr float U() const { return UV.X; }
	        /// <summary> Gets the position of the vertex along the texture v-axis. </summary>
            constexpr float V() const { return UV.Y; }
	        /// <summary> Gets the position of the vertex along the model space x-axis. </summary>
            constexpr float X() const { return Position.X; }
	        /// <summary> Gets the position of the vertex along the model space y-axis. </summary>
            constexpr float Y() const { return Position.Y; }
	        /// <summary> Gets the position of the vertex along the model space z-axis. </summary>
            constexpr float Z() const { return Position.Z; }

	        /// <summary> Sets the position of the vertex along the texture u-axis. </summary>
            void U(float u)           { UV.X = u; }
	        /// <summary> Sets the position of the vertex along the texture v-axis. </summary>
            void V(float v)           { UV.Y = v; }
	        /// <summary> Sets the position of the vertex along the model space x-axis. </summary>
            void X(float x)           { Position.X = x; }
	        /// <summary> Sets the position of the vertex along the model space y-axis. </summary>
            void Y(float y)           { Position.Y = y; }
	        /// <summary> Sets the position of the vertex along the model space z-axis. </summary>
            void Z(float z)           { Position.Z = z; }



            /** CONSTRUCTORS **/
            /// <summary> Constructs a default vertex positioned at the origin (0, 0, 0) with texture coordinates (0, 0). </summary>
            constexpr Vertex()                                                          : Position(0), UV(0) { }
            /// <summary> Constructs a vertex with a designated position and texture coordinates. </summary>
            /// <param name="position"> A three-element vector specifying the (x, y, z) coordinates of the vertex. </param>
            /// <param name="uv"> A two-element vector specifying the (u, v) coordinates of an associated texture. </param>
            constexpr Vertex(const Vector3& position, const Vector2& uv)                : Position(position), UV(uv) { }
            /// <summary> Constructs a vertex with a designated position and texture coordinates. </summary>
            /// <param name="x"> The desired x-coordinate of the vertex. </param>
            /// <param name="y"> The desired y-coordinate of the vertex. </param>
            /// <param name="z"> The desired z-coordinate of the vertex. </param>
            /// <param name="u"> The desired u-coordinate of the texture associated with the vertex. </param>
            /// <param name="v"> The desired v-coordinate of the texture associated with the vertex. </param>
            constexpr Vertex(float x, float y, float z, float u = 0.0f, float v = 0.0f) : Position(x, y, z), UV(u, v) { }

        };
    }
}