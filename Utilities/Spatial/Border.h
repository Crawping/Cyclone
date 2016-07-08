/* CHANGELOG
 * Written by Josh Grooms on 20150921
 */

#pragma once
#include "TypeDefinitions.h"
#include "UtilitiesAPI.h"
struct Area;



namespace Cyclone::Utilities
{
    /* BORDER - A data structure that describes the border of a two-dimensional rectangular region of space.
     *
     *      'Border' is a data type that is closely related to 'Area', and one might use both to describe a more complicated area
     *      of space composed of a central region and a surrounding border of varying thicknesses. However, unlike 'Area', for
     *      which there is really only one clear definition, the definition of the 'Border' data structure is intentionally left
     *      more open to interpretation. This is because the individual segment values could conceivably be used in several
     *      different ways. For example, they could represent the thickness of a border surrounding an area, the lengths of each
     *      edge of the rectangle, or the absolute positions of a rectangle's edges (i.e. as an alternative to using 'Area'
     *      structures).
     */
    struct UtilitiesAPI Border
    {
        /** STATIC DATA **/
        /* EMPTY - A border whose edge segments all have a value of 0.0f. */
        const static Border Empty;
        /* UNIT - A border whose edge segments all have a value of 1.0f. */
        const static Border Unit;



        /** DATA **/
        /* TOP - The value of the top border segment. */
        float Top;
        /* BOTTOM - The value of the bottom border segment. */
        float Bottom;
        /* LEFT - The value of the left border segment. */
        float Left;
        /* RIGHT - The value of the right border segment. */
        float Right;



        /** CONSTRUCTORS **/
        /* BORDER - Constructs an empty border data structure. */
        Border();
        /* BORDER - Constructs a border with the specified edge segments. */
        Border(float top, float bottom, float left, float right);



        /** UTILITIES **/
        /* FLIP - Flips the border about one of its two dimensions.
         *
         *      This method effectively swaps the values of two opposing edges of the border. Which set of edges are flipped is
         *      controlled by the 'dim' argument that defaults to flipping the border vertically (i.e. the top and bottom edges
         *      are swapped). Flipping always occurs across x- or y-axis-aligned midlines; performing flips across arbitrary axes
         *      is not supported.
         *
         *      SYNTAX:
         *          B = B.Flip(dim)
         *
         *      OUTPUT:
         *          B:      Border&
         *                  A reference to the flipped and modified original area. This output is provided to facilitate the
         *                  chaining of multiple methods together on in a single line of code.
         *
         *      INPUT:
         *          dim:    uint
         *                  An unsigned integer specifying the dimension across which the flip will occur.
         */
        Border& Flip(uint dim);

        string Report() const;

    };
}