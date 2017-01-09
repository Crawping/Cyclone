#include "Console.h"
#include "Matrix4x4.h"
#include "Utilities.h"
#include <iomanip>
#include <sstream>
#include <cstring>



namespace Cyclone
{
    namespace Utilities
    {
        /** INTERNAL DATA **/
        const static float EYE[16] =
        {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
        };
        const static float ONE[16] =
        {
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
        };
        const static float ZERO[16] =
        {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
        };



        /** CONSTANT DATA **/
        const Matrix4x4 Matrix4x4::Identity     = Matrix4x4(EYE);
        const Matrix4x4 Matrix4x4::One          = Matrix4x4(ONE);
        const Matrix4x4 Matrix4x4::Zero         = Matrix4x4(ZERO);



        /** CONSTRUCTORS **/
        Matrix4x4::Matrix4x4()                          : Matrix4x4(EYE) { }
        Matrix4x4::Matrix4x4(const Matrix4x4& other)    : Matrix4x4(other.Data)  { }
        Matrix4x4::Matrix4x4(const float* other)
        {
            memcpy(Data, other, sizeof(Data));
        }
        Matrix4x4::Matrix4x4(std::initializer_list<float> values)
        {
            int idx = 0;
            for (float v : values)
                Data[idx++] = v;
        }



        /** UTILITIES **/
        Matrix4x4 Matrix4x4::Inverse() const
        {
            const Matrix4x4& state = *this;

            float s0 = (state(0, 0) * state(1, 1)) - (state(1, 0) * state(0, 1));
            float s1 = (state(0, 0) * state(1, 2)) - (state(1, 0) * state(0, 2));
            float s2 = (state(0, 0) * state(1, 3)) - (state(1, 0) * state(0, 3));
            float s3 = (state(0, 1) * state(1, 2)) - (state(1, 1) * state(0, 2));
            float s4 = (state(0, 1) * state(1, 3)) - (state(1, 1) * state(0, 3));
            float s5 = (state(0, 2) * state(1, 3)) - (state(1, 2) * state(0, 3));

            float c5 = (state(2, 2) * state(3, 3)) - (state(3, 2) * state(2, 3));
            float c4 = (state(2, 1) * state(3, 3)) - (state(3, 1) * state(2, 3));
            float c3 = (state(2, 1) * state(3, 2)) - (state(3, 1) * state(2, 2));
            float c2 = (state(2, 0) * state(3, 3)) - (state(3, 0) * state(2, 3));
            float c1 = (state(2, 0) * state(3, 2)) - (state(3, 0) * state(2, 2));
            float c0 = (state(2, 0) * state(3, 1)) - (state(3, 0) * state(2, 1));

            float invdet = 1.0f / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

            Matrix4x4 inverse;

            inverse(0, 0) = ( state(1, 1) * c5 - state(1, 2) * c4 + state(1, 3) * c3 ) * invdet;
            inverse(0, 1) = (-state(0, 1) * c5 + state(0, 2) * c4 - state(0, 3) * c3 ) * invdet;
            inverse(0, 2) = ( state(3, 1) * s5 - state(3, 2) * s4 + state(3, 3) * s3 ) * invdet;
            inverse(0, 3) = (-state(2, 1) * s5 + state(2, 2) * s4 - state(2, 3) * s3 ) * invdet;

            inverse(1, 0) = (-state(1, 0) * c5 + state(1, 2) * c2 - state(1, 3) * c1 ) * invdet;
            inverse(1, 1) = ( state(0, 0) * c5 - state(0, 2) * c2 + state(0, 3) * c1 ) * invdet;
            inverse(1, 2) = (-state(3, 0) * s5 + state(3, 2) * s2 - state(3, 3) * s1 ) * invdet;
            inverse(1, 3) = ( state(2, 0) * s5 - state(2, 2) * s2 + state(2, 3) * s1 ) * invdet;

            inverse(2, 0) = ( state(1, 0) * c4 - state(1, 1) * c2 + state(1, 3) * c0 ) * invdet;
            inverse(2, 1) = (-state(0, 0) * c4 + state(0, 1) * c2 - state(0, 3) * c0 ) * invdet;
            inverse(2, 2) = ( state(3, 0) * s4 - state(3, 1) * s2 + state(3, 3) * s0 ) * invdet;
            inverse(2, 3) = (-state(2, 0) * s4 + state(2, 1) * s2 - state(2, 3) * s0 ) * invdet;

            inverse(3, 0) = (-state(1, 0) * c3 + state(1, 1) * c1 - state(1, 2) * c0 ) * invdet;
            inverse(3, 1) = ( state(0, 0) * c3 - state(0, 1) * c1 + state(0, 2) * c0 ) * invdet;
            inverse(3, 2) = (-state(3, 0) * s3 + state(3, 1) * s1 - state(3, 2) * s0 ) * invdet;
            inverse(3, 3) = ( state(2, 0) * s3 - state(2, 1) * s1 + state(2, 2) * s0 ) * invdet;

            return inverse;
        }
        string Matrix4x4::ToString() const
        {
            std::stringstream msg;
            msg << "\n";
            for (int a = 0; a < 4; a++)
            {
                for (int b = 0; b < 13; b+= 4)
                    msg << std::setw(10) << std::right << Data[a + b];
                msg << "\n";
            }
            return msg.str();
        }
        Matrix4x4& Matrix4x4::Transpose()
        {
            for (int a = 0; a < 4; a++)
                for (int b = 0; b < a; b++)
                    std::swap(Data[sub2ind(4, 4, a, b)], Data[sub2ind(4, 4, b, a)]);
            return *this;
        }



        /** INDEXING OPERATORS **/
        float Matrix4x4::operator ()(uint idx)                 const
        {
            return Data[idx];
        }
        float Matrix4x4::operator ()(uint a, uint b)           const
        {
            return Data[sub2ind(4, 4, a, b)];
        }

        float& Matrix4x4::operator ()(uint idx)
        {
            if (idx >= Count())
            {
                Console::WriteLine("Attempted to access a matrix using an out-of-bounds index.");
                return Data[0];
            }
            else
                return Data[idx];
        }
        float& Matrix4x4::operator ()(uint a, uint b)
        {
            int idx = sub2ind(4, 4, a, b);
            if (idx == -1)
            {
                Console::WriteLine("Attempted to access a matrix using out-of-bounds indices.");
                return Data[0];
            }
            else
                return Data[idx];
        }

        //Vector4 Matrix4x4::operator ()(char a, uint b)         const
        //{
        //    int idx = b * 4;
        //    return Vector4(Data[idx], Data[idx + 1], Data[idx + 2], Data[idx + 3]);
        //}

        //Vector4 Matrix4x4::operator ()(uint a, char b)         const
        //{
        //    return Vector4(Data[a], Data[a + 4], Data[a + 8], Data[a + 12]);
        //}



        /** MATH OPERATORS **/
        bool Matrix4x4::operator ==(const Matrix4x4& m)        const
        {
            if (this == (const Matrix4x4*)&m)
                return true;

            for (int a = 0; a < 16; a++)
                if (Data[a] != m.Data[a])
                    return false;

            return true;
        }

        Matrix4x4 Matrix4x4::operator +(float m)               const
        {
            Matrix4x4 result(*this);
            result += m;
            return result;
        }
        Matrix4x4 Matrix4x4::operator +(const Matrix4x4& m)    const
        {
            Matrix4x4 result(*this);
            result += m;
            return result;
        }

        Matrix4x4 Matrix4x4::operator /(float m)               const
        {
            Matrix4x4 result(*this);
            result /= m;
            return result;
        }
        Matrix4x4 Matrix4x4::operator /(const Matrix4x4& m)    const
        {
            Matrix4x4 result(*this);
            result /= m;
            return result;
        }

        Matrix4x4 Matrix4x4::operator *(float m)               const
        {
            Matrix4x4 result(*this);
            result *= m;
            return result;
        }
        Matrix4x4 Matrix4x4::operator *(const Matrix4x4& m)    const
        {
            int idxM, idxN, idxR;
            Matrix4x4 result(Matrix4x4::Zero);

            for (int a = 0; a < 16; a++)
            {
                idxM = a % 4;
                idxN = a / 4;
                idxR = idxN * 4;

                for (int b = 0; b < 4; b++)
                    result.Data[a] += Data[idxM + (b * 4)] * m.Data[idxR + b];
            }

            return result;
        }
        Vector4 Matrix4x4::operator *(const Vector4& v)        const
        {
            return Vector4
            (
                (Data[0] * v.X) + (Data[4] * v.Y) + (Data[ 8] * v.Z) + (Data[12] * v.W),
                (Data[1] * v.X) + (Data[5] * v.Y) + (Data[ 9] * v.Z) + (Data[13] * v.W),
                (Data[2] * v.X) + (Data[6] * v.Y) + (Data[10] * v.Z) + (Data[14] * v.W),
                (Data[3] * v.X) + (Data[7] * v.Y) + (Data[11] * v.Z) + (Data[15] * v.W)
            );
        }

        Matrix4x4 Matrix4x4::operator -(float m)               const
        {
            Matrix4x4 result(*this);
            result -= m;
            return result;
        }
        Matrix4x4 Matrix4x4::operator -(const Matrix4x4& m)    const
        {
            Matrix4x4 result(*this);
            result -= m;
            return result;
        }

        Matrix4x4& Matrix4x4::operator +=(float m)
        {
            for (int a = 0; a < 16; a++)
                Data[a] += m;
            return *this;
        }
        Matrix4x4& Matrix4x4::operator +=(const Matrix4x4& m)
        {
            for (int a = 0; a < 16; a++)
                Data[a] += m.Data[a];
            return *this;
        }

        Matrix4x4& Matrix4x4::operator /=(float m)
        {
            for (int a = 0; a < 16; a++)
                Data[a] /= m;
            return *this;
        }
        Matrix4x4& Matrix4x4::operator /=(const Matrix4x4& m)
        {
            for (int a = 0; a < 16; a++)
                Data[a] /= m.Data[a];
            return *this;
        }

        Matrix4x4& Matrix4x4::operator *=(float m)
        {
            for (int a = 0; a < 16; a++)
                Data[a] *= m;
            return *this;
        }
        Matrix4x4& Matrix4x4::operator *=(const Matrix4x4& m)
        {
            Matrix4x4 result = operator *(m);
            memcpy(Data, result.Data, sizeof(Data));
            return *this;
        }

        Matrix4x4& Matrix4x4::operator -=(float m)
        {
            for (int a = 0; a < 16; a++)
                Data[a] -= m;
            return *this;
        }
        Matrix4x4& Matrix4x4::operator -=(const Matrix4x4& m)
        {
            for (int a = 0; a < 16; a++)
                Data[a] -= m.Data[a];
            return *this;
        }


        Vector4 operator *(const Vector4& v, const Matrix4x4& m)
        {
            return Vector4
            (
                v.X * m(0) + v.Y * m(1) + v.Z * m(2) + v.W * m(3),
                v.X * m(4) + v.Y * m(5) + v.Z * m(6) + v.W * m(7),
                v.X * m(8) + v.Y * m(9) + v.Z * m(10) + v.W * m(11),
                v.X * m(12) + v.Y * m(13) + v.Z * m(14) + v.W * m(15)
            );
        }
    }
}
