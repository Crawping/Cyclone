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



        /** UTILITIES **/
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
                for (int b = 0; b < a; a++)
                    std::swap(operator ()(a, b), operator ()(b, a));
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

        Vector4 Matrix4x4::operator ()(char a, uint b)         const
        {
            int idx = b * 4;
            return Vector4(Data[idx], Data[idx + 1], Data[idx + 2], Data[idx + 3]);
        }

        Vector4 Matrix4x4::operator ()(uint a, char b)         const
        {
            return Vector4(Data[a], Data[a + 4], Data[a + 8], Data[a + 12]);
        }



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
    }
}