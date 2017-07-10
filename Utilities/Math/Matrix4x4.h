/* CHANGELOG
 * Written by Josh Grooms on 20160526
 */

#pragma once
#include "Vector4.h"



namespace Cyclone
{
    namespace Utilities
    {
         /// <summary> A data structure representing a square matrix with four rows and four columns of 32-bit floating point values. </summary>
        struct UtilitiesAPI Matrix4x4
        {
            public:

                /** CONSTANT DATA **/
                /// <summary> A 4x4 identity matrix. </summary>
                const static Matrix4x4 Identity;
		        /// <summary> A 4x4 matrix whose elements all equal 1.0f. </summary>
                const static Matrix4x4 One;
		        /// <summary> A 4x4 matrix whose elements all equal 0.0f. </summary>
                const static Matrix4x4 Zero;



                /** PROPERTIES **/
		        /// <summary> Gets the total number of elements in this matrix. </summary>
                uint Count()            const { return 16; }
		        /// <summary> Gets the number of dimensions of this array. </summary>
                uint Rank()             const { return 2; }



                /** CONSTRUCTORS **/
		        /// <summary> Constructs a new 4x4 identity matrix. </summary>
                /// <returns>
                ///     A new data structure representing a 4x4 matrix of single-precision floating <para/>
                ///     point values that form an identity matrix.
                /// </returns>
                Matrix4x4();
		        /// <summary> Constructs a new 4x4 matrix as a deep copy of a flattened native array. </summary> 
		        /// <param name="other">
		        ///		A native C++ array of single-precision floating point values to be copied.
                ///     <para> </para>
		        ///		This array should be flat (i.e. one-dimensional) and arranged in column-major   <para/>
		        ///		order. It must also have at least 16 elements(though only the first 16 will be   <para/>
		        ///		used).
		        /// </param>
		        /// <returns>
		        ///		A new data structure representing a 4x4 matrix of single-precision floating <para/>
		        ///		point values copied from the inputted array 'other'.
		        /// </returns>
                Matrix4x4(const float* other);
                /// <summary> Constructs a new 4x4 matrix as a deep copy of another matrix. </summary>
                /// <param name="other"> An existing 4x4 matrix whose elements are to be copied. </param>
                /// <returns> 
                ///     A new data structure representing a 4x4 matrix of single-precision floating
                ///     point values copied from the inputted matrix <paramref name="other"/>. 
                /// </returns>
                Matrix4x4(const Matrix4x4& other);
                /// <summary> Constructs a new 4x4 matrix by copying the elements of an initializer list. </summary>
                /// <param name="values"> A flattened list of numbers in column-major ordering. </param>
                Matrix4x4(std::initializer_list<float> values);


                /** UTILITIES **/

                Matrix4x4 Inverse()                         const;
                /// <summary> Gets the pointer to the native data array stored by this object. </summary>
                /// <returns> A pointer to the first single-precision float value in this matrix. </returns>
                /// <remarks> 
                ///     This method retrieves the backing data store for a matrix, without making a deep copy of it. Thus, any modifications 
                ///     made to the array referenced by the outputted pointer will also affect the original matrix, warranting some caution 
                ///     with its use. It is provided as a convenience for dealing with other libraries and code (e.g. OpenGL) that also use 
                ///     matrices.
                /// </remarks>
                float* ToArray()                                  { return Data; }
                /// <summary> Gets the pointer to the native data array stored by this object. </summary>
                /// <returns> A constant pointer to the first single-precision float value in this matrix. </returns>
                const float* ToArray()                      const { return Data; }
                /// <summary> Rearranges the matrix elements such that rows become columns and vice versa. </summary>
                Matrix4x4& Transpose();
                /// <summary> Converts this matrix into a formatted, human-readable string containing all element values. </summary>
                string ToString() const;



                /** INDEXING OPERATORS **/
                float& operator [](uint idx)                      { return Data[idx]; }
        
                float operator ()(uint idx)                 const;
                float operator ()(uint a, uint b)           const;

                float& operator ()(uint idx);
                float& operator ()(uint a, uint b);

    

                /** MATH OPERATORS **/
                bool operator ==(const Matrix4x4& m)        const;
                bool operator !=(const Matrix4x4& m)        const { return !(operator ==(m)); }

                /// <summary> Adds the inputted scalar value to each element of this matrix. </summary>
                Matrix4x4 operator +(float m)               const;
                /// <summary> Adds each element of the inputted matrix to the corresponding element of this matrix. </summary>
                Matrix4x4 operator +(const Matrix4x4& m)    const;

                /// <summary> Divides each element of this matrix by the inputted scalar value. </summary>
                Matrix4x4 operator /(float m)               const;
                /// <summary> Divides each element of this matrix by the corresponding element of the inputted matrix. </summary>
                Matrix4x4 operator /(const Matrix4x4& m)    const;

                /// <summary> Multiplies each element of this matrix by the inputted scalar value. </summary>
                Matrix4x4 operator *(float m)               const;
                /// <summary> Multiplies two equivalently sized matrices. </summary>
                Matrix4x4 operator *(const Matrix4x4& m)    const;
                /// <summary> Multiplies the matrix by a four-element vector. </summary>
                Vector4 operator *(const Vector4& v)        const;

                /// <summary> Multiplies each element of this matrix by -1.0f, changing their signs. </summary>
                Matrix4x4 operator -()                      const { return operator *(-1.0f); }
                /// <summary> Subtracts the inputted scalar value from each element of this matrix. </summary>
                Matrix4x4 operator -(float m)               const;
                /// <summary> Subtracts each element of the inputted matrix from the corresponding element of this matrix. </summary>
                Matrix4x4 operator -(const Matrix4x4& m)    const;

                Matrix4x4& operator +=(float m);
                Matrix4x4& operator +=(const Matrix4x4& m);

                Matrix4x4& operator /=(float m);
                Matrix4x4& operator /=(const Matrix4x4& m);

                Matrix4x4& operator *=(float m);
                Matrix4x4& operator *=(const Matrix4x4& m);

                Matrix4x4& operator -=(float m);
                Matrix4x4& operator -=(const Matrix4x4& m);

            private:

                /// <summary> The raw native array of values held by this matrix. </summary>
                float Data[16];

        };


        UtilitiesAPI Vector4 operator *(const Vector4& v, const Matrix4x4& m);

    }
}