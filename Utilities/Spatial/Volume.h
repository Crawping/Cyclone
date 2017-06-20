/* CHANGELOG
 * Written by Josh Grooms on 20160507
 */

#pragma once
#include "TypeDefinitions.h"
#include "Collections/Array.h"
#include "Math/Math.h"
#include "Math/Vector3.h"
#include "Spatial/Area.h"
#include "Spatial/LineSegment.h"



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
            const static Volume Empty; //= Volume { 0, 0, 0, 0, 0, 0 };
            /// <summary> A rectangular prism with unit volume positioned at the origin (0, 0, 0). </summary>
            const static Volume Unit;// = Volume { 0, 0, 0, 1, 1, 1 };



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

            /// <summary> Gets the (x, y, z) coordinates of the back-lower-left corner of this volume. </summary>
            constexpr Vector3 Position()                const { return Vector3(X, Y, Z); }
            /// <summary> Sets the (x, y, z) coordinates of the back-lower-left corner of this volume. </summary>
            Volume& Position(const Vector3& p)                { X = p.X; Y = p.Y; Z = p.Z; return *this; }
            /// <summary> Sets the (x, y, z) coordinates of the back-lower-left corder of this volume. </summary>
            Volume& Position(float x, float y, float z)       { X = x; Y = y; Z = z; return *this; }

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
                X(x), Y(y), Z(z),
                Width(width), Height(height), Depth(depth)
            {

            }



            /** UTILITIES **/
            /// <summary> Determines whether a point lies within the bounds of the volume. </summary>
            /// <returns> A Boolean <c>true</c> if the point's coordinates lie inside of the volume, or <c>false</c> otherwise. </returns>
            /// <param name="point"> The point to be tested. </param>
            /// <param name="inclusive"> 
            ///     An Boolean <c>true</c> if points on the boundary of the volume should be considered contained, or <c>false</c> 
            ///     otherwise. 
            /// </param>
            /// <remarks>
            ///     This method tests whether a particular point lies within or on the bounds of a volume in 3D space. Note that this 
            ///     means any point whose coordinates fall exactly on the bounds of the rectangular prism is considered contained and 
            ///     thus will pass the inspection.
            /// </remarks>
            constexpr bool Contains(const Vector3& point, bool inclusive = true) const
            {
                return
                    Math::IsBetween(point.X, Left(), Right(), inclusive) &&
                    Math::IsBetween(point.Y, Bottom(), Top(), inclusive) &&
                    Math::IsBetween(point.Z, Back(), Front(), inclusive);
            }
            /// <summary> Determines whether this volume completely contains another one. </summary>
            /// <returns> A Boolean <c>true</c> if the inputted volume fits within this one, or <c>false</c> otherwise. </returns>
            /// <param name="volume"> Another volume data structure to be tested. </param>
            /// <param name="inclusive"> 
            ///     An Boolean <c>true</c> if points on the boundary of the volume should be considered contained, or <c>false</c> 
            ///     otherwise. 
            /// </param>
            /// <remarks>
            ///     This method tests the edge locations of two volume descriptions to determine if one fits within the other. Passing 
            ///     the test requires that one volume (on which this method is called) be positioned and sized such that it contains a 
            ///     smaller or equivalently sized volume (the input argument). Note that this means two identical volumes are considered 
            ///     to contain one another and thus will pass the inspection.
            /// </remarks>
            constexpr bool Contains(const Volume& volume, bool inclusive = true) const
            {
                return 
                    Math::IsBetween(volume.Left(), Left(), Right(), inclusive)      &&
                    Math::IsBetween(volume.Right(), Left(), Right(), inclusive)     &&
                    Math::IsBetween(volume.Bottom(), Bottom(), Top(), inclusive)    &&
                    Math::IsBetween(volume.Top(), Bottom(), Top(), inclusive)       &&
                    Math::IsBetween(volume.Back(), Back(), Front(), inclusive)      &&
                    Math::IsBetween(volume.Front(), Back(), Front(), inclusive);
            }
            /// <summary> Determines the region of space shared by both this and another volume. </summary>
            /// <returns> An empty volume if no intersection exists, or the region of space where the two volumes overlap. </returns>
            /// <param name="volume"> Another overlapping volume of space. </param>
            constexpr Volume Intersection(const Volume& volume) const
            {
                if (!Intersects(volume)) return Volume(0, 0, 0, 0, 0, 0);

                auto v1 = Rectify(), v2 = volume.Rectify();
                float x = Math::Max(v1.Left(), v2.Left());
                float y = Math::Max(v1.Bottom(), v2.Bottom());
                float z = Math::Max(v1.Back(), v2.Back());

                float w = Math::Min(v1.Right(), v2.Right()) - x;
                float h = Math::Min(v1.Top(), v2.Top()) - y;
                float d = Math::Min(v1.Front(), v2.Front()) - z;

                return Volume(x, y, z, w, h, d);
            }
            /// <summary> Determines whether this volume shares any space with another one. </summary>
            /// <param name="volume"> Another volume to be tested for overlap. </param>
            /// <returns> A Boolean <c>true</c> if the two volumes have overlapping regions of space, or <c>false</c> otherwise. </returns>
            constexpr bool Intersects(const Volume& volume) const
            {
                auto v1 = Rectify(), v2 = volume.Rectify();
                return
                    v1.Left() <= v2.Right() && v1.Right() >= v2.Left() &&
                    v1.Bottom() <= v2.Top() && v1.Top() >= v2.Bottom() &&
                    v1.Back() <= v2.Front() && v1.Front() >= v2.Back();
            }
            /// <summary> Determines whether this volume intersects a line segment. </summary>
            /// <returns> A Boolean <c>true</c> if the line segment intersects the volume, or <c>false</c> otherwise. </returns>
            /// <param name="line"> A line segment to be tested for intersection. </param>
            constexpr bool Intersects(const LineSegment3D& line) const
            {
                return false;
            }
            /// <summary> Converts this volume into an equivalent one whose size consists only of positive values. </summary>
            /// <returns> A positive volume whose position represents the back-lower-left corner of the prism. </returns>
            constexpr Volume Rectify() const
            {
                return Volume
                (
                    Math::Min(Left(), Right()), Math::Min(Bottom(), Top()), Math::Min(Front(), Back()),
                    Math::Abs(Width), Math::Abs(Height), Math::Abs(Depth)
                );
            }
            /// <summary> Generates a human-readable string detailing the current state of the data structure. </summary>
            string Report() const;

            constexpr Array<float, 6> ToArray()             const { return { X, Y, Z, Width, Height, Depth }; }
            
            constexpr Volume Union(const Volume& volume)    const
            {
                auto v1 = Rectify(), v2 = volume.Rectify();
                float x = Math::Min(v1.Left(), v2.Left());
                float y = Math::Min(v1.Bottom(), v2.Bottom());
                float z = Math::Min(v1.Back(), v2.Back());

                float w = Math::Max(v1.Right(), v2.Right()) - x;
                float h = Math::Max(v1.Top(), v2.Top()) - y;
                float d = Math::Max(v1.Front(), v2.Front()) - z;

                return Volume(x, y, z, w, h, d);
            }


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



