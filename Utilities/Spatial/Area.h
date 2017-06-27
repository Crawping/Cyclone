/* CHANGELOG
 * Written by Josh Grooms on 20150915
 */

#pragma once
#include "Math/Math.h"
#include "Math/Vector2.h"



namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> A data structure that describes a two-dimensional rectangular region of space. </summary>
        /// <remarks> 
        ///     Documentation throughout this structure assumes usage of an upright, 2D coordinate system. Care should be taken 
        ///     when using other axes configurations (e.g. image and window space with their inverted y-axes) so as not to create 
        ///     confusion.
        /// </remarks>
        struct UtilitiesAPI Area
        {

            /** CONSTANT DATA **/
            /// <summary> A region with zero width and height at the origin (0, 0). </summary>
            const static Area Empty;
            /// <summary> A region with unit width and height whose lower-left corner is at the origin (0, 0). </summary>
            const static Area Unit;



            /** DATA **/
            /// <summary> The x-axis coordinate for the lower-left corner of the rectangular area. </summary>
            float X;
            /// <summary> The y-axis coordinate for the lower-left corner of the rectangular area. </summary>
            float Y;
            /// <summary> The extent of the area along the x-axis. </summary>
            float Width;
            /// <summary> The extent of the area along the y-axis. </summary>
            float Height;



            /** PROPERTIES **/
            /// <summary> Gets the y-axis coordinate of the area's bottom edge. </summary>
            /// <remarks> Note that this is equivalent to getting the Y coordinate of the area directly. </remarks>
            constexpr float Bottom()        const { return Y; }
            /// <summary> Gets the x-axis coordinate of the area's left edge. </summary>
            /// <remarks> Note that this is equivalent to getting the X coordinate of the area directly. </remarks>
            constexpr float Left()          const { return X; }
            /// <summary> Gets the x-axis coordinate of the area's right edge. </summary>
            /// <remarks> The right edge of the area is calculated by adding the width of the area to its left edge coordinate. </remarks>
            constexpr float Right()         const { return X + Width; }
            /// <summary> Gets the y-axis coordinate of the area's top edge. </summary>
            /// <remarks> The top edge of the area is calculated by adding the height of the area to its bottom edge coordinate. </remarks>
            constexpr float Top()           const { return Y + Height; }

            /// <summary> Determines whether this region has a total area of zero. </summary>
            constexpr bool IsEmpty()        const { return (Width == 0) || (Height == 0); }
            /// <summary> Determines whether this region represents a positive, non-zero area. </summary>
            constexpr bool IsPositive()     const { return (Width > 0) && (Height > 0); }

            /// <summary> Gets the (x, y) coordinates for the center of the rectangular area. </summary>
            constexpr Vector2 Center()      const { return Vector2((Right() - Left()) / 2.0f, (Top() - Bottom()) / 2.0f); }
            /// <summary> Gets the (x, y) coordinates for the lower-left corner of the rectangular area. </summary>
            constexpr Vector2 Position()    const { return Vector2(X, Y); }
            /// <summary> Gets the width and height of the rectangular area. </summary>
            constexpr Vector2 Scale()       const { return Vector2(Width, Height); }

            /// <summary> Sets the y-axis coordinate of the area's bottom edge. </summary>
            /// <remarks>
            ///     Although getting this value is the same as reading the y-coordinate directly, note that setting the bottom edge
            ///     is not equivalent to setting the Y member of this structure. Instead, this setter method controls edge position
            ///     independently of all other edges by also modifying the height of the area. This allows the bottom edge to move
            ///     freely in space while the top edge position remains unchanged.
            /// </remarks>
            void Bottom(float y)                  { Height = Top() - y; Y = y; }
            /// <summary> Sets the x-axis coordinate of the area's left edge. </summary>
            /// <remarks>
            ///     Although getting this value is the same as reading the x-coordinate directly, note that setting the left edge 
            ///     is not equivalent to setting the X member of this structure. Instead, this setter method controls edge position
            ///     independently of all other edges by also modifying the height of the area. This allows the left edge to move
            ///     freely in space while the right edge position remains unchanged.
            /// </remarks>
            void Left(float x)                    { Width = Right() - x; X = x; }
            /// <summary> Sets the x-axis coordinate of the area's right edge. </summary>
            /// <remarks>
            ///     Setting this value modifies the width of the area so that the x-axis location of the left edge does not change. 
            ///     This allows all four edges of the rectangular area to be manipulated independently of one another.
            /// </remarks>
            void Right(float x)                   { Width = x - X; }
            /// <summary> Sets the y-axis coordinate of the area's top edge. </summary>
            /// <remarks>
            ///     Setting this value modifies the height of the area so that the y-axis location of the bottom edge does not
            ///     change. This allows all four edges of the rectangular area to be manipulated independently of one another.
            /// </remarks>
            void Top(float y)                     { Height = y - Y; }

            /// <summary> Sets the (x, y) coordinates for the lower-left corner of the rectangular area. </summary>
            Area& Position(const Vector2& p)      { X = p.X; Y = p.Y; return *this; }
            /// <summary> Sets the (x, y) coordinates for the lower-left corner of the rectangular area. </summary>
            Area& Position(float x, float y)      { X = x; Y = y; return *this; }
            /// <summary> Sets the width and height of the rectangular area. </summary>
            Area& Scale(const Vector2& s)         { Width = s.X; Height = s.Y; return *this; }
            /// <summary> Sets the width and height of the rectangular area. </summary>
            Area& Scale(float x, float y)         { Width = x; Height = y; return *this; }



            /** CONSTRUCTORS **/
            /// <summary> Constructs a default data structure describing a rectangle located at the origin and with zero area. </summary>
            constexpr Area():                       Area(0, 0, 0, 0) { }
            /// <summary> Constructs an area data structure with a designated position and size. </summary>
            /// <param name="x"> The desired x-coordinate of the region's lower-left corner. </param>
            /// <param name="y"> The desired y-coordinate of the region's lower-left corner. </param>
            /// <param name="width"> The desired width of the region. </param>
            /// <param name="height"> The desired height of the region. </param>
            constexpr Area(float x, float y, float width, float height):
                X(x), Y(y),
                Width(width),
                Height(height)
            {

            }
            /// <summary> Constructs an area data structure with a designated position and size. </summary>
            /// <param name="position"> A two-element vector containing the (x, y) coordinates of the region's lower-left corner. </param>
            /// <param name="size"> A two-element vector containing the (x, y) sizes of the region. </param>
            constexpr Area(const Vector2& position, const Vector2& size):
                Area(position.X, position.Y, size.X, size.Y)
            {

            }



            /** UTILITIES **/
            /// <summary> Determines whether another area fits inside of this one. </summary>
            /// <param name="other"> A reference to the Area structure whose region will be tested to fit within this one. </param>
            /// <returns>
            ///     A Boolean <c>true</c> if this area contains the inputted one, or <c>false</c> otherwise.
            ///     <para> </para>
            ///     Edge coordinates that are equal to one another across the two area structures are considered contained.
            /// </returns>
            /// <remarks>
            ///     This method tests the edge locations of two area descriptions to determine if one fits within the other. 
            ///     Passing the test requires that one large area (on which this method is called) be positioned and sized such 
            ///     that it contains a smaller or equivalently sized area (the input argument <paramref name="other"/>). In 
            ///     contrast to the related method <see cref="Surrounds"/>, two equivalent areas here are considered contained 
            ///     and thus pass the inspection.
            /// </remarks>
            constexpr bool Contains(const Area& other, bool inclusive = true)       const
            {
                return
                    Math::IsBetween(other.Left(), Left(), Right(), inclusive)   &&
                    Math::IsBetween(other.Right(), Left(), Right(), inclusive)  && 
                    Math::IsBetween(other.Bottom(), Bottom(), Top(), inclusive) && 
                    Math::IsBetween(other.Top(), Bottom(), Top(), inclusive);
            }
            /// <summary> Determines whether a particular point lies within this area. </summary>
            /// <param name="point"> A two-element vector containing the (x, y) coordinates of the point to be tested. </param>
            /// <returns> A Boolean <c>true</c> if the point lies within or on the border of the area, or <c>false</c> otherwise. </returns>
            constexpr bool Contains(const Vector2& point, bool inclusive = true)    const
            {
                return
                    Math::IsBetween(point.X, Left(), Right(), inclusive) && 
                    Math::IsBetween(point.Y, Bottom(), Top(), inclusive);
            }
            /// <summary> Flips the rectangular area about one of its two dimensions. </summary>
            /// <returns> A reference to the flipped (and original) area. </returns>
            /// <param name="dim"> An unsigned integer specifying the dimension across which the rectangle will be flipped. </param>
            /// <remarks>
            ///     This method effectively swaps the values of two opposing edges on the rectangular area. Which set of edges are
            ///     flipped is controlled by the <paramref name="dim"/> argument. Inputting a value of <c>0</c> results in a flip 
            ///     across the area's vertical midline, meaning the <see cref="Left"/> and <see cref="Right"/> values will be swapped 
            ///     and the <see cref="Width"/> of the area will change sign. Inputting a value of <c>1</c> will result in a flip 
            ///     across the area's horizontal midline. Flipping always occurs across x- or y-axis-aligned midlines within the 
            ///     rectangular area; performing flips across arbitrary axes is not supported.
            /// </remarks>
            constexpr Area Flip(uint dim)                   const
            {
                return dim ? 
                    Area(X, Top(), Width, -Height) : 
                    Area(Right(), Y, -Width, Height);
            }
            /// <summary> Determines the region of space shared by both this and another volume. </summary>
            /// <returns> An empty area, if no intersection exists, or the region of space where the two areas overlap. </returns>
            /// <param name="other"> Another overlapping area of space. </param>
            constexpr Area Intersection(const Area& other)  const
            {
                if (!Intersects(other)) { return Area(0, 0, 0, 0); }

                auto a1 = Rectify(), a2 = other.Rectify();
                float x = Math::Max(a1.Left(), a2.Left());
                float y = Math::Max(a1.Bottom(), a2.Bottom());
                float w = Math::Min(a1.Right(), a2.Right()) - x;
                float h = Math::Min(a1.Top(), a2.Top()) - y;

                return Area(x, y, w, h);
            }
            /// <summary> Determines whether two separate areas share any overlapping regions. </summary>
            /// <returns> A Boolean <c>true</c> if the two areas have overlapping regions of space, or <c>false</c> otherwise. </returns>
            constexpr bool Intersects(const Area& other)    const
            {
                auto a1 = Rectify(), a2 = other.Rectify();
                return
                    a1.Left() <= a2.Right() && a1.Right() >= a2.Left() && 
                    a1.Bottom() <= a2.Top() && a1.Top() >= a2.Bottom();
            }

            Area& Normalize();
            /// <summary> Corrects the area position to reflect the true lower-left corner of the rectangle. </summary>
            constexpr Area Rectify()                        const
            {
                return Area
                (
                    Math::Min(Left(), Right()),
                    Math::Min(Bottom(), Top()),
                    Math::Abs(Width),
                    Math::Abs(Height)
                );
            }
            /// <summary> Returns a formatted string that describes the boundaries of this rectangular area. </summary>
            string Report()                                 const;
            /// <summary> Sets the position of the lower left area corner relative to its current location. </summary>
            Area& Translate(const Vector2& t)               { X += t.X; Y += t.Y; return *this; }
            /// <summary> Sets the position of the lower left area corner relative to its current location. </summary>
            Area& Translate(float x, float y)               { return Translate(Vector2(x, y)); }
            /// <summary> Combines two separate areas into a single one that fully contains both of them. </summary>
            constexpr Area Union(const Area& other)         const
            {
                auto a1 = Rectify(), a2 = other.Rectify();
                float x = Math::Min(a1.Left(), a2.Left());
                float y = Math::Min(a1.Bottom(), a2.Bottom());
                float w = Math::Max(a1.Right(), a2.Right()) - x;
                float h = Math::Max(a1.Top(), a2.Top()) - y;
                return Area(x, y, w, h);
            }



            /** OPERATORS **/
            /// <summary> Determines whether two areas are equivalent to one another. </summary>
            /// <returns> A Boolean <c>true</c> if the two areas are identical, or <c>false</c> otherwise. </returns>
            constexpr bool operator ==(const Area& other)   const
            {
                return (X == other.X) && (Y == other.Y) && (Width == other.Width) && (Height == other.Height);
            }
            /// <summary> Determines whether two areas are not equivalent to one another. </summary>
            /// <returns> A Boolean <c>true</c> if the two areas are not identical, or <c>false</c> otherwise. </returns>
            constexpr bool operator !=(const Area& other)   const { return !(*this == other); }

        };
    }
}
