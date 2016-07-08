/* CHANGELOG
 * Written by Josh Grooms on 20160517
 */

#pragma once
#include "Vector2.h"



namespace Cyclone
{
    namespace Utilities
    {    
        struct Color4;


        /// <summary> A class that holds and manages a two-dimensional array of RGBA pixel colors. </summary>
        class Bitmap
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the height of this bitmap image in pixels. </summary>
                uint Height()           const { return (uint)_size.Y; }
                /// <summary> Determines whether this bitmap has any zero-length dimensions. </summary>
                bool IsEmpty()          const { return Height() == 0 || Width() == 0; }
                /// <summary> Gets the total number of pixels present in this bitmap. </summary>
                uint Length()           const { return Height() * Width(); }
                /// <summary> Gets the width and height of this bitmap as a two-element vector. </summary>
                const Vector2& Size()   const { return _size; }
                /// <summary> Gets the width of this bitmap image in pixels. </summary>
                uint Width()            const { return (uint)_size.X; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs a matrix of RGBA color values representing a bitmap image. </summary>
                /// <param name="size"> 
                ///     A two-element vector specifying the desired width and height of the bitmap in pixels.
                ///		<para> </para>
                ///     The X component of this vector represents bitmap pixel width, while the Y component <para/>
                ///     height. Fractional parts of the two float values are completely ignored.
                /// </param>
		        UtilitiesAPI Bitmap(const Vector2& size);
                /// <summary> Constructs a RGBA bitmap image that is a deep copy of another bitmap. </summary>
                /// <param name="other"> A bitmap instance whose pixel array is to be copied. </param>
		        UtilitiesAPI Bitmap(const Bitmap& other);
                /// <summary> Moves a RGBA bitmap image into a new data structure. </summary>
		        UtilitiesAPI Bitmap(Bitmap&& other);
                /// <summary> Frees the heap-allocated pixel array managed by this bitmap. </summary>
		        UtilitiesAPI ~Bitmap();



                /** UTILITIES **/
		        UtilitiesAPI Bitmap& Allocate(const Vector2& size);
		        UtilitiesAPI Bitmap& Fill(const Color4& color);
                UtilitiesAPI string Report() const;



                /** OPERATORS **/
                Color4* ToArray() { return Pixels; }

		        UtilitiesAPI Color4& operator ()(int a, int b);

		        UtilitiesAPI Bitmap& operator =(Bitmap& other);
		        UtilitiesAPI Bitmap& operator =(Bitmap&& other);


            private:

                Vector2 _size;

                /// <summary> A native array of color values comprising the pixel data for this bitmap. </summary>
                /// <remarks>
                ///     This array is meant to be interpretted as through it were a 2D matrix of pixel colors, 
                ///     but is actually stored and addressed as a flattened vector of values(in column-major 
                ///     format).
                /// </remarks>
                Color4* Pixels;
        };
    }
}