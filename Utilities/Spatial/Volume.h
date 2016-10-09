/* CHANGELOG
 * Written by Josh Grooms on 20160507
 */

#pragma once
#include "TypeDefinitions.h"
#include "Spatial/Area.h"
#include "Math/Vector3.h"



//namespace Cyclone::Utilities
//{
namespace Cyclone
{
    namespace Utilities
    {

        /// <summary> A data structure that describes a three-dimensional rectangular prism occupying a volume of space. </summary>
        /// <remarks> Documentation throughout this structure assumes usage of a right-handed 3D coordinate system. </remarks>
        struct UtilitiesAPI Volume
        {

            /** CONSTANT DATA **/
            /// <summary> A rectangular prism whose position and size are all equal to zero. </summary>
            const static Volume Empty;
            /// <summary> A rectangular prism with unit volume positioned at the origin (0, 0, 0). </summary>
            const static Volume Unit;



            /** DATA **/
            /// <summary> The x-axis coordinate for the back-lower-left corner of the rectangular prism. </summary>
            float X;
            /// <summary> The y-axis coordinate for the back-lower-left corner of the rectangular prism. </summary>
            float Y;
            /// <summary> The z-axis coordinate for the back-lower-left corner of the rectangular prism. </summary>
            float Z;

            /// <summary> The extent of the volume along the x-axis. </summary>
            float Width;
            /// <summary> The extent of the volume along the y-axis. </summary>
            float Height;
            /// <summary> The extent of the volume along the z-axis. </summary>
            float Depth;



            /** PROPERTIES **/
            /// <summary> Gets the z-axis coordinate of the volume's far plane. </summary>
            /// <remarks> Note that this is equivalent to getting the z-coordinate of the volume directly. </remarks>
            constexpr float Back()                      const { return Z; }
            /// <summary> Gets the y-axis coordinate of the volume's bottom plane. </summary>
            /// <remarks> Note that this is equivalent to getting the y-coordinate of the volume directly. </remarks>
            constexpr float Bottom()                    const { return Y; }
            /// <summary> Gets the z-axis coordinate of the volume's near plane. </summary>
            /// <remarks> The front plane position is calculated by adding the depth to the back plane position. </remarks>
            constexpr float Front()                     const { return Z + Depth; }
            /// <summary> Gets the x-axis coordinate of the volume's left plane. </summary>
            /// <remarks> Note that this is equivalent to getting the x-coordinate of the volume directly. </remarks>
            constexpr float Left()                      const { return X; }
            /// <summary> Gets the x-axis coordinate of the volume's right plane. </summary>
            /// <remarks> The right plane position is calculated by adding the width to the left plane position. </remarks>
            constexpr float Right()                     const { return X + Width; }
            /// <summary> Gets the y-axis coordinate of the volume's top plane. </summary>
            /// <remarks> The top plane position is calculated by adding the height to the bottom plane position. </remarks>
            constexpr float Top()                       const { return Y + Height; }

            /// <summary> Determines whether this rectangular prism has a total volume of zero. </summary>
            constexpr bool IsEmpty()                    const { return !Width || !Height || !Depth; }

            /// <summary> Gets the (x, y, z) coordinates of the front-lower-left corner of this volume. </summary>
            constexpr Vector3 Position()                const { return Vector3(X, Y, Z); }
            /// <summary> Sets the (x, y, z) coordinates of the front-lower-left corner of this volume. </summary>
            Volume& Position(const Vector3& p)                { X = p.X; Y = p.Y; Z = p.Z; return *this; }
            /// <summary> Sets the (x, y, z) coordinates of the front-lower-left corder of this volume. </summary>
            Volume& Position(float x, float y, float z)       { X = x, Y = y, Z = z; return *this; }

            /// <summary> Gets the (width, height, depth) values of this volume. </summary>
            constexpr Vector3 Size()                    const { return Vector3(Width, Height, Depth); }
            /// <summary> Sets the (width, height, depth) values of this volume. </summary>
            Volume& Size(const Vector3& s)                    { Width = s.X; Height = s.Y; Depth = s.Z; return *this; }
            /// <summary> Sets the (width, height, depth) values of this volume. </summary>
            Volume& Size(float x, float y, float z)           { Width = x; Height = y; Depth = z; return *this; }



            /** CONSTRUCTORS **/
            /// <summary> Constructs a default data structure describing a unit rectangular prism at the origin (0, 0, 0). </summary>
            constexpr Volume() :
                X(0), Y(0), Z(0),
                Width(1), Height(1), Depth(1)
            {

            }
            /// <summary> Constructs a volume data structure by extruding a 2D rectangular area along the z-axis. </summary>
            /// <param name="area"> A two-dimensional region of space to be converted into a three-dimensional volume. </param>
            /// <param name="depth"> The desired size of the resulting volume along the z-axis. </param>
            constexpr Volume(const Area& area, float depth = 1.0f) :
                X(area.X), Y(area.Y), Z(0.0f),
                Width(area.Width), Height(area.Height), Depth(depth)
            {

            }
            /// <summary> Constructs a data structure describing a rectangular prism with a designated position and size. </summary>
            constexpr Volume(const Vector3& position, const Vector3& size) :
                X(position.X), Y(position.Y), Z(position.Z),
                Width(size.X), Height(size.Y), Depth(size.Z)
            {

            }
            /// <summary> Constructs a data structure describing a rectangular prism with a designated position and size. </summary>
            constexpr Volume(float x, float y, float z, float width, float height, float depth) :
                X(x), Y(x), Z(z),
                Width(width), Height(height), Depth(depth)
            {

            }



            /** UTILITIES **/
            /// <summary> Determines whether a point lies within the bounds of the volume. </summary>
            /// <returns> A Boolean <c>true</c> if the point's coordinates lie inside of the volume, or <c>false</c> otherwise. </returns>
            /// <param name="point"> The </param>
            /// <remarks>
            ///     This method tests whether a particular point lies within or on the bounds of a volume in 3D space. Note that this 
            ///     means any point whose coordinates fall exactly on the bounds of the rectangular prism is considered contained and 
            ///     thus will pass the inspection.
            /// </remarks>
            constexpr bool Contains(const Vector3& point) const;
            /// <summary> Determines whether this volume completely contains another one. </summary>
            /// <returns> A Boolean <c>true</c> if the inputted volume fits within this one, or <c>false</c> otherwise. </returns>
            /// <param name="volume"> Another <see cref="Volume"/> data structure to be tested. </param>
            /// <remarks>
            ///     This method tests the edge locations of two volume descriptions to determine if one fits within the other. Passing 
            ///     the test requires that one volume (on which this method is called) be positioned and sized such that it contains a 
            ///     smaller or equivalently sized volume (the input argument). Note that this means two identical volumes are considered 
            ///     to contain one another and thus will pass the inspection.
            /// </remarks>
            constexpr bool Contains(const Volume& volume) const;
            /// <summary> Generates a human-readable string detailing the current state of the data structure. </summary>
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
}



