/* CHANGELOG
 * Written by Josh Grooms on 20150921
 */

#pragma once
#include "TypeDefinitions.h"
#include "UtilitiesAPI.h"



namespace Cyclone
{
    namespace Utilities
    {
        struct Area;


        /// <summary> A data structure that describes the border of a two-dimensional rectangular region of space. </summary>
        /// <remarks>
        ///     'Border' is a data type that is closely related to 'Area', and one might use both to describe a more complicated area
        ///     of space composed of a central region and a surrounding border of varying thicknesses. However, unlike 'Area', for
        ///     which there is really only one clear definition, the definition of the 'Border' data structure is intentionally left
        ///     more open to interpretation. This is because the individual segment values could conceivably be used in several
        ///     different ways. For example, they could represent the thickness of a border surrounding an area, the lengths of each
        ///     edge of the rectangle, or the absolute positions of a rectangle's edges (i.e. as an alternative to using 'Area'
        ///     structures).
        /// </remarks>
        struct UtilitiesAPI Border
        {
            /** STATIC DATA **/
            /// <summary> A border whose edge segments all have a value of 0.0f. </summary>
            const static Border Empty;
            /// <summary> A border whose edge segments all have a value of 1.0f. </summary>
            const static Border Unit;



            /** DATA **/
            /// <summary> The value of the top border segment. </summary>
            float Top;
            /// <summary> The value of the bottom border segment. </summary>
            float Bottom;
            /// <summary> The value of the left border segment. </summary>
            float Left;
            /// <summary> The value of the right border segment. </summary>
            float Right;



            /** CONSTRUCTORS **/
            /// <summary> Constructs an empty border data structure. </summary>
            Border();
            /// <summary> Constructs a border with the specified edge segments. </summary>
            Border(float top, float bottom, float left, float right);



            /** UTILITIES **/
            /// <summary> Flips the border about one of its two dimensions. </summary>
            /// <returns> 
            ///     A reference to the flipped and modified original border.
            ///     <para> </para>
            ///     This output is provided to facilitate the chaining of method calls. 
            /// </returns>
            /// <param name="dim"> An unsigned integer specifying the dimension across which the flip will occur. </param>
            /// <remarks>
            ///     This method effectively swaps the values of two opposing edges of the border. Which set of edges are flipped is
            ///     controlled by the 'dim' argument that defaults to flipping the border vertically (i.e. the top and bottom edges
            ///     are swapped). Flipping always occurs across x- or y-axis-aligned midlines; performing flips across arbitrary axes
            ///     is not supported.
            /// </remarks>
            Border& Flip(uint dim);
            /// <summary> Generates a human-readable string detailing the current internal state of the border object. </summary>
            string Report() const;

        };
    }
}
