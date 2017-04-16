/* CHANGELOG
 * Written by Josh Grooms on 20160517
 */

#pragma once
#include "Collections/Vector.h"
#include "Math/Vector3.h"



namespace Cyclone
{
    namespace Utilities
    {
        struct Color4;


        /// <summary> A class that holds and manages a three-dimensional array of RGBA pixel colors. </summary>
        class Bitmap : public virtual ICollection<Color4>
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the number of pixels along the z-axis of the bitmap image. </summary>
                uint Depth()            const { return (uint)_size.Z; }
                /// <summary> Gets the number of pixels along the y-axis of the bitmap image. </summary>
                uint Height()           const { return (uint)_size.Y; }
                /// <summary> Determines whether the bitmap has any zero-length dimensions. </summary>
                bool IsEmpty()          const override { return _pixels.IsEmpty(); }
                /// <summary> Gets the total number of pixels present in the bitmap. </summary>
                uint Count()            const override { return _pixels.Count(); }
                /// <summary> Gets the width, height, and depth of the bitmap as a three-element vector. </summary>
                const Vector3& Size()   const { return _size; }
                /// <summary> Gets the number of pixels along the x-axis of the bitmap image. </summary>
                uint Width()            const { return (uint)_size.X; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs an array of RGBA color values representing a bitmap image. </summary>
                /// <param name="size"> A three-element vector specifying the desired width, height, and depth of the bitmap in pixels. </param>
		        UtilitiesAPI Bitmap(const Vector3& size = Vector3::Zero);
                /// <summary> Constructs a RGBA bitmap image that is a deep copy of another bitmap. </summary>
                /// <param name="other"> A bitmap instance whose pixel array is to be copied. </param>
		        UtilitiesAPI Bitmap(const Bitmap& other);
                /// <summary> Moves a RGBA bitmap image into a new data structure. </summary>
		        UtilitiesAPI Bitmap(Bitmap&& other);



                /** UTILITIES **/
		        UtilitiesAPI void Fill(const Color4& color);
                UtilitiesAPI string Report() const;



                /** OPERATORS **/
                Color4* ToArray()                                                   { return _pixels.ToArray(); }
                const Color4* ToArray()                                             const { return _pixels.ToArray(); }
                const Vector<Color4>& ToVector()                                    const { return _pixels; }

                UtilitiesAPI Color4& operator() (uint index);
                UtilitiesAPI const Color4& operator() (uint index)                  const;
		        UtilitiesAPI Color4& operator ()(uint a, uint b, uint c = 0);
                UtilitiesAPI const Color4& operator ()(uint a, uint b, uint c = 0)  const;

		        UtilitiesAPI Bitmap& operator =(Bitmap& other);
		        UtilitiesAPI Bitmap& operator =(Bitmap&& other);

            protected:

                /** UTILITIES **/
                UtilitiesAPI virtual void Reallocate(const Vector3& size);

            private:

                /// <summary> A native array of color values comprising the pixel data for the bitmap. </summary>
                /// <remarks>
                ///     This array is meant to be interpretted as through it were a 2D matrix of pixel colors,
                ///     but is actually stored and addressed as a flattened vector of values(in column-major
                ///     format).
                /// </remarks>
                Vector<Color4>  _pixels;
                Vector3         _size;

        };
    }
}
