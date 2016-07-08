/* CHANGELOG
 * Written by Josh Grooms on 20160507
 */

#pragma once
#include "Area.h"
#include "Vector3.h"



namespace Cyclone::Utilities
{
    /// <summary> A data structure that describes a three-dimensional rectangular prism occupying a volume of space. </summary>
    struct UtilitiesAPI Volume
    {

        /** CONSTANT DATA **/
        /// <summary> A rectangular prism whose position and size are all equal to zero. </summary>
        const static Volume Empty;
        /// <summary> A rectangular prism with unit volume positioned at the origin (0, 0, 0). </summary>
        const static Volume Unit;



        /** DATA **/
        /// <summary> The x-axis coordinate for the front-lower-left corner of the rectangular prism. </summary>
        float X;
        /// <summary> The y-axis coordinate for the front-lower-left corner of the rectangular prism. </summary>
        float Y;
        /// <summary> The z-axis coordinate for the front-lower-left corner of the rectangular prism. </summary>
        float Z;

        /// <summary> The extent of the volume along the x-axis. </summary>
        float Width;
        /// <summary> The extent of the volume along the y-axis. </summary>
        float Height;
        /// <summary> The extent of the volume along the z-axis. </summary>
        float Depth;



        /** PROPERTIES **/
        constexpr float Back()                      const { return Z + Depth; }
        constexpr float Bottom()                    const { return Y; }
        constexpr float Front()                     const { return Z; }
        constexpr float Left()                      const { return X; }
        constexpr float Right()                     const { return X + Width; }
        constexpr float Top()                       const { return Y + Height; }

        /* ISEMPTY - Determines whether this rectangular prism has a total volume of zero. */
        constexpr bool IsEmpty()                    const { return !Width || !Height || !Depth; }

        /* POSITION - Gets the (x, y, z) coordinates of the front-lower-left corner of this volume. */
        constexpr Vector3 Position()                const { return Vector3(X, Y, Z); }
        /* POSITION - Sets the (x, y, z) coordinates of the front-lower-left corner of this volume. */
        Volume& Position(const Vector3& p)                { X = p.X; Y = p.Y; Z = p.Z; return *this; }
        /* POSITION - Sets the (x, y, z) coordinates of the front-lower-left corder of this volume. */
        Volume& Position(float x, float y, float z)       { X = x, Y = y, Z = z; return *this; }

        /* SIZE - Gets the (width, height, depth) values of this volume. */
        constexpr Vector3 Size()                    const { return Vector3(Width, Height, Depth); }
        /* SIZE - Sets the (width, height, depth) values of this volume. */
        Volume& Size(const Vector3& s)                    { Width = s.X; Height = s.Y; Depth = s.Z; return *this; }
        /* SIZE - Sets the (width, height, depth) values of this volume. */
        Volume& Size(float x, float y, float z)           { Width = x; Height = y; Depth = z; return *this; }



        /** CONSTRUCTORS **/
        /* VOLUME - Constructs a default data structure describing a unit rectangular prism at the origin (0, 0, 0). */
        constexpr Volume() :
            X(0), Y(0), Z(0),
            Width(1), Height(1), Depth(1)
        {

        }
        constexpr Volume(const Area& area) :
            X(area.X), Y(area.Y), Z(0.0f),
            Width(area.Width), Height(area.Height), Depth(1.0f)
        {

        }
        /* VOLUME - Constructs a data structure describing a rectangular prism with a designated position and size. */
        constexpr Volume(const Vector3& position, const Vector3& size) :
            X(position.X), Y(position.Y), Z(position.Z),
            Width(size.X), Height(size.Y), Depth(size.Z)
        {

        }
        /* VOLUME - Constructs a data structure describing a rectangular prism with a designated position and size. */
        constexpr Volume(float x, float y, float z, float width, float height, float depth) :
            X(x), Y(x), Z(z),
            Width(width), Height(height), Depth(depth)
        {

        }



        /** UTILITIES **/
        string Report() const;



        /** OPERATORS **/
        constexpr bool operator ==(const Volume& other) const
        {
            return X == other.X && Y == other.Y && Z == other.Z &&
                Width == other.Width && Height == other.Height && Depth == other.Depth;
        }
        constexpr bool operator !=(const Volume& other) const { return !(*this == other); }
    };
}