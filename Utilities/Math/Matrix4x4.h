/* CHANGELOG
 * Written by Josh Grooms on 20160526
 */

#pragma once
#include "Vector4.h"



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
        Matrix4x4();
        /* MATRIX4x4 - Constructs a new 4x4 matrix as a deep copy of a flattened native array.
         *
         *      SYNTAX:
         *          M = Matrix4x4(other)
         *
         *      <OUTPUT>:
         *          M:      Matrix4x4
         *                  A new data structure representing a 4x4 matrix of single-precision floating point values copied
         *                  from the inputted array 'other'.
         *
         *      <INPUT>:
         *          other:  const float*
         *                  A native C++ array of single-precision floating point values to be copied. This array should be
         *                  flat (i.e. one-dimensional) and arranged in column-major order. It must also have at least 16
         *                  elements (though only the first 16 will be used).
         */

		/// <summary> Constructs a new 4x4 matrix as a deep copy of a flattened native array. </summary> 
		/// <param name="other">
		///		A native C++ array of single - precision floating point values to be copied. <para/>
		///		This array should be flat(i.e.one - dimensional) and arranged in column-major <para/>
		///		order.It must also have at least 16 elements(though only the first 16 will be <para/>
		///		used).
		/// </param>
		/// <returns>
		///		A new data structure representing a 4x4 matrix of single-precision floating <para/>
		///		point values copied from the inputted array 'other'.
		/// </returns>
        Matrix4x4(const float* other);
        /* MATRIX4x4 - Constructs a new 4x4 matrix as a deep copy of another matrix.
         *
         *      SYNTAX:
         *          M = Matrix4x4(other)
         *
         *      OUTPUT:
         *          M:      Matrix4x4
         *                  A new data structure representing a 4x4 matrix of single-precision floating point values copied
         *                  from the inputted matrix 'other'.
         *
         *      INPUT:
         *          other:  const Matrix4x4&
         *                  An existing 4x4 matrix data structure whose elements will be copied into the newly created
         *                  matrix 'M'.
         */
        Matrix4x4(const Matrix4x4& other);



        /** UTILITIES **/
        float* ToArray()                                  { return Data; }

        const float* ToArray()                      const { return Data; }
        /* TRANSPOSE - Rearranges the matrix elements such that rows become columns and vice versa. */
        Matrix4x4& Transpose();

        string ToString() const;



        /** INDEXING OPERATORS **/
        float& operator [](uint idx)                      { return Data[idx]; }

        float operator ()(uint idx)                 const;
        float operator ()(uint a, uint b)           const;

        float& operator ()(uint idx);
        float& operator ()(uint a, uint b);

        Vector4 operator ()(char a, uint b)         const;
        Vector4 operator ()(uint a, char b)         const;



        /** MATH OPERATORS **/
        bool operator ==(const Matrix4x4& m)        const;
        bool operator !=(const Matrix4x4& m)        const { return !(operator ==(m)); }

        /* ADDITION - Adds the inputted scalar value to each element of this matrix. */
        Matrix4x4 operator +(float m)               const;
        /* ADDITION - Adds each element of the inputted matrix to the corresponding element of this matrix. */
        Matrix4x4 operator +(const Matrix4x4& m)    const;

        /* DIVISION - Divides each element of this matrix by the inputted scalar value. */
        Matrix4x4 operator /(float m)               const;
        /* DIVISION - Divides each element of this matrix by the corresponding element of the inputted matrix. */
        Matrix4x4 operator /(const Matrix4x4& m)    const;

        /* MULTIPLICATION - Multiplies each element of this matrix by the inputted scalar value. */
        Matrix4x4 operator *(float m)               const;
        /* MULTIPLICATION - Multiplies two equivalently sized matrices. */
        Matrix4x4 operator *(const Matrix4x4& m)    const;

        /* NEGATION - Multiplies each element of this matrix by -1.0f, changing their signs. */
        Matrix4x4 operator -()                      const { return operator *(-1.0f); }
        /* SUBTRACTION - Subtracts the inputted scalar value from each element of this matrix. */
        Matrix4x4 operator -(float m)               const;
        /* SUBTRACTION - Subtracts each element of the inputted matrix from the corresponding element of this matrix. */
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
        /* DATA - The raw native array of values held by this matrix. */
        float Data[16];
};
