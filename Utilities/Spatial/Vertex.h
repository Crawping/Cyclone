/* CHANGELOG
 * Written by Josh Grooms on 20150907
 */

#pragma once
#include "Vector2.h"
#include "Vector3.h"



namespace Cyclone::Utilities
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
        constexpr Vertex()                                                          : Position(0), UV(0) { }
        constexpr Vertex(const Vector3& position, const Vector2& uv)                : Position(position), UV(uv) { }
        constexpr Vertex(float x, float y, float z, float u = 0.0f, float v = 0.0f) : Position(x, y, z), UV(u, v) { }

    };
}