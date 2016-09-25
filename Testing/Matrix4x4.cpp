/* CHANGELOG
 * Written by Josh Grooms on 20160710
 */

#include "Math/Matrix4x4.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



/** INTERNAL DATA **/
struct CanonicalMatrices
{
    const float Eye[16] = 
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    const float One[16] = 
    {
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
    };
    const float Zero[16] =
    {
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
    };


    const Vector4 V1 = Vector4(0.276922984960890f, 0.046171390631154f, 0.097131781235848f, 0.823457828327293f);

    const float M1[16] = 
    {
        0.814723686393179f,   0.632359246225410f,   0.957506835434298f,   0.957166948242946f,
        0.905791937075619f,   0.097540404999410f,   0.964888535199277f,   0.485375648722841f,
        0.126986816293506f,   0.278498218867048f,   0.157613081677548f,   0.800280468888800f,
        0.913375856139019f,   0.546881519204984f,   0.970592781760616f,   0.141886338627215f,
    };
    const float M2[16] = 
    {
        0.421761282626275f,   0.655740699156587f,   0.678735154857773f,   0.655477890177557f,
        0.915735525189067f,   0.035711678574190f,   0.757740130578333f,   0.171186687811562f,
        0.792207329559554f,   0.849129305868777f,   0.743132468124916f,   0.706046088019609f,
        0.959492426392903f,   0.933993247757551f,   0.392227019534168f,   0.031832846377421f,
    };
    const float M1M2[16] = 
    {
        1.622471640610552f,   0.878161136234862f,   1.779735641925979f,   1.358158372894797f,
        1.030999567654624f,   0.887205270669930f,   1.196863134662114f,   1.524539036548191f,
        2.153818031047046f,   1.176868672165795f,   2.380269700286890f,   1.865314054064516f,
        1.706607773587276f,   0.824489308885090f,   1.912636773716241f,   1.690140285290024f,
    };
    const float M1V1[4] =
    {
        2.111426086369138f,
        1.077390030426642f,
        2.354286101599818f,
        2.019435883589503f,
    };

    

};





class _Matrix4x4 : public ::testing::Test
{
    protected:
        CanonicalMatrices Canon;

        Matrix4x4 _m0;
        Matrix4x4 _m1;
        Matrix4x4 _m2;
        Matrix4x4 _m3;

        Matrix4x4 _m4;
        Matrix4x4 _m5;
        Matrix4x4 _m6;

        Vector4     _v1;
        

        _Matrix4x4() : 
            _m1(Matrix4x4::Identity),
            _m2(Matrix4x4::One),
            _m3(Matrix4x4::Zero),
            _m4(Canon.M1),
            _m5(Canon.M2)
            {
                _m6 = _m4 * _m5;
                _v1 = _m6 * Canon.V1;
            }
};



/** CONSTRUCTOR TESTS **/
TEST_F(_Matrix4x4, DefaultConstruction)
{
    ASSERT_EQ(_m0.Count(), 16);
    for (uint a = 0; a < _m0.Count(); a++)
        ASSERT_EQ(_m0(a), Canon.Eye[a]);
}

TEST_F(_Matrix4x4, CopyConstruction)
{
    for (uint a = 0; a < _m1.Count(); a++)
    {
        ASSERT_EQ(_m2(a), Canon.One[a]);
        ASSERT_EQ(_m3(a), Canon.Zero[a]);
    }

    Matrix4x4 _m2Copy(_m2);
    ASSERT_NE(_m2, _m2Copy + 5.0f);
}



/** OPERATOR TESTS **/
TEST_F(_Matrix4x4, EqualityOperators)
{
    ASSERT_EQ(_m0, _m1);
    ASSERT_NE(_m0, _m2);
}

TEST_F(_Matrix4x4, IndexingOperators)
{
    uint idx = 0;
    for (uint a = 0; a < 4; a++)
        for (uint b = 0; b < 4; b++)
        {
            ASSERT_EQ(_m4(idx), Canon.M1[idx]);
            ASSERT_EQ(_m4(b, a), Canon.M1[idx++]);
        }
}

TEST_F(_Matrix4x4, AdditionOperators)
{
    ASSERT_EQ(_m0, _m1 + Matrix4x4::Zero);
    ASSERT_EQ(_m2, _m3 + 1.0f);
}

TEST_F(_Matrix4x4, MatrixMultiplication)
{
    for (uint a = 0; a < _m6.Count(); a++)
        ASSERT_FLOAT_EQ(_m6(a), Canon.M1M2[a]);
}

TEST_F(_Matrix4x4, VectorMultiplication)
{
    ASSERT_FLOAT_EQ(_v1.X, Canon.M1V1[0]);
    ASSERT_FLOAT_EQ(_v1.Y, Canon.M1V1[1]);
    ASSERT_FLOAT_EQ(_v1.Z, Canon.M1V1[2]);
    ASSERT_FLOAT_EQ(_v1.W, Canon.M1V1[3]);
}