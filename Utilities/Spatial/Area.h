/* CHANGELOG
 * Written by Josh Grooms on 20150915
 */

#pragma once
#include "Vector2.h"



namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> A data structure that describes a two-dimensional rectangular region of space. </summary>
        struct UtilitiesAPI Area
        {

            /** CONSTANT DATA **/
            const static Area Empty;
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
            float Bottom()                  const { return Y; }
            /// <summary> Gets the x-axis coordinate of the area's left edge. </summary>
            /// <remarks> Note that this is equivalent to getting the X coordinate of the area directly. </remarks>
            float Left()                    const { return X; }
            /// <summary> Gets the x-axis coordinate of the area's right edge. </summary>
            /// <remarks> The right edge of the area is calculated by adding the width of the area to its left edge coordinate. </remarks>
            float Right()                   const { return X + Width; }
            /// <summary> Gets the y-axis coordinate of the area's top edge. </summary>
            /// <remarks> The top edge of the area is calculated by adding the height of the area to its bottom edge coordinate. </remarks>
            float Top()                     const { return Y + Height; }

            /// <summary> Gets the (x, y) coordinates for the lower-left corner of the rectangular area. </summary>
            Vector2 Position()              const { return Vector2(X, Y); }
            /// <summary> Gets the width and height of the rectangular area. </summary>
            Vector2 Scale()                 const { return Vector2(Width, Height); }

            /// <summary> Sets the y-axis coordinate of the area's bottom edge. </summary>
            /// <remarks>
            ///     Although getting this value is the same as reading the y - coordinate directly, note that setting the bottom edge
            ///     is not equivalent to setting the Y member of this structure.Instead, this setter method controls edge position
            ///     independently of all other edges by also modifying the height of the area.This allows the bottom edge to move
            ///     freely in space while the top edge position remains unchanged.
            /// </remarks>
            void Bottom(float y)                  { Height = Top() - y; Y = y; }
            /// <summary> Sets the x-axis coordinate of the area's left edge. </summary>
            /// <remarks>
            ///     Although getting this value is the same as reading the x - coordinate directly, note that setting the left edge is
            ///     not equivalent to setting the X member of this structure.Instead, this setter method controls edge position
            ///     independently of all other edges by also modifying the height of the area.This allows the left edge to move
            ///     freely in space while the right edge position remains unchanged.
            /// </remarks>
            void Left(float x)                    { Width = Right() - x; X = x; }
            /// <summary> Sets the x-axis coordinate of the area's right edge. </summary>
            /// <remarks>
            ///     Setting this value modifies the width of the area so that the x - axis location of the left edge does not change.
            ///     This allows all four edges of the rectangular area to be manipulated independently of one another.
            /// </remarks>
            void Right(float x)                   { Width = x - X; }
            /// <summary> Sets the y-axis coordinate of the area's top edge. </summary>
            /// <remarks>
            ///     Setting this value modifies the height of the area so that the y - axis location of the bottom edge does not
            ///     change.This allows all four edges of the rectangular area to be manipulated independently of one another.
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
            Area();
            /// <summary> Constructs an area data structure with a designated position and size. </summary>
            Area(float x, float y, float width, float height);



            /** UTILITIES **/
            /// <summary> Determines whether or not another area fits inside of this one. </summary>
            /// <param name="other">
            ///     A reference to the Area structure whose region will be tested to fit within an area 'A'.
            /// </param>
            /// <returns>
            ///     A Boolean indicating whether or not the area in 'A' contains the area in 'other'. 
            ///     <para> </para>
            ///     If 'other' lies within a larger area 'A', then a Boolean true is returned. Otherwise, <para/>
            ///     this method returns false. Edge coordinates that are equal to one another across the <para/>
            ///     two area structures are considered contained.
            /// </returns>
            /// <remarks>
            ///     This method tests the edge locations of two area descriptions to determine if one fits within the other. Passing
            ///     the test requires that one large area(on which this method is called) be positioned and sized such that it
            ///     contains a smaller or equivalently sized area(the input argument 'other').In contrast to the related method
            ///     'Surrounds', two equivalent areas here are considered contained and thus pass the inspection.
            /// </remarks>
            bool Contains(const Area& other) const;

            bool Contains(const Vector2& point) const;
            /// <summary> Contrains an area such that its edge coordinates lie on or within another area. </summary>
            /// <param name="keep">
            ///     A reference to the smaller area that will be used to resize the larger 'A' one. 
            ///     <para> </para>
            ///     As a typical example, this could be a small rectangular area within 'A' that should <para/>
            ///     be kept, while the rest of the surrounding region in 'A' should be cropped away, rather <para/>
            ///     like the cropping of an image.
            /// </param>
            /// <returns>
            ///     A reference to the cropped(and the larger original) area.This output is provided to facilitate the
            ///     chaining of multiple methods together in a single line of code operating on an Area structure.
            /// </returns>
            /// <remarks>
            ///     This method resizes a large area(the one on which this method is called) to fit within an inputted smaller area.
            ///     It accomplishes this by comparing the edge coordinates of the two data structures, keeping the largest left and
            ///     bottom values as well as the lowest right and top coordinates.These values are then used to replace the original
            ///     ones in the larger area.
            /// </remarks>
            Area& Crop(const Area& keep);
            /// <summary> Flips the rectangular area about one of its two dimensions. </summary>
            /// <param name="dim">
            ///     An unsigned integer specifying the dimension across which the rectangle will be flipped. 
            ///     <para> </para>
            ///     By default, areas are flipped across the first dimension(i.e.the x - axis), resulting in the left and right edge
            ///     coordinates being swapped with one another.
            ///     DEFAULT: 1
            ///     OPTIONS: 1 or 2
            /// </param>
            /// <returns>
            ///     A reference to the flipped(and original) area.This output is provided to facilitate the chaining of
            ///     multiple methods together in a single line of code operating on an Area structure.
            /// </returns>
            /// <remarks>
            ///     This method effectively swaps the values of two opposing edges on the rectangular area.Which set of edges are
            ///     flipped is controlled by the 'dim' argument that defaults to flipping the area vertically(i.e.the top and
            ///     bottom edge coordinates are swapped).Flipping always occurs x - or y - axis - aligned midlines within the rectangular
            ///     area; performing flips across arbitrary axes is not supported.
            /// </remarks>            
            Area& Flip(uint dim);
            /// <summary> Determines whether or not two separate areas share any overlapping regions. </summary>
            bool Intersects(Area other) const;
            /// <summary> Determines whether or not this region has a total area of zero. </summary>
            bool IsEmpty() const                { return (Width == 0) || (Height == 0); }
            /// <summary> Determines whether or not this region represents a positive, non-zero area. </summary>
            bool IsPositive() const             { return (Width > 0) && (Height > 0); }

            Area& Normalize();
            /// <summary> Corrects the area position to reflect the true lower-left corner of the rectangle. </summary>
            Area& Rectify();
            /// <summary> Returns a formatted string that describes the boundaries of this rectangular area. </summary>
            string Report() const;
            /// <summary>
            ///     Determines whether or not another area fits inside of this one without overlapping their edges.
            /// </summary>
            /// <param name="other">
            ///     A reference to the Area structure whose region will be tested to be surrounded by the area 'A'.
            /// </param>
            /// <returns>
            ///     A Boolean indicating whether or not the area in 'A' surrounds the area in 'other'.
            /// </returns>
            /// <remarks>
            ///     This method tests the edge locations of two area desciptions to determine if one fits within the other.Passing
            ///     the test requires that one large area(on which this method is called) be positioned and such that it fully
            ///     surrounds a smaller area(the input argument 'other').Unlike the related method 'Contains', two equivalent areas
            ///     are not considered to surround one another and thus fail the inspection.
            /// </remarks>
            bool Surrounds(const Area& other) const;
            /// <summary> Sets the position of the lower left area corner relative to its current location. </summary>
            Area& Translate(Vector2 t)          { X += t.X; Y += t.Y; return *this; }
            /// <summary> Sets the position of the lower left area corner relative to its current location. </summary>
            Area& Translate(float x, float y)   { X += x; Y += y; return *this; }
            /// <summary> Combines two separate areas into a single one that fully contains both of them. </summary>
            Area& Union(const Area& other);



            /** OPERATORS **/
            bool operator ==(const Area& other) const;
            bool operator !=(const Area& other) const { return !(*this == other); }

        };
    }
}