/* CHANGELOG
 * Written by Josh Grooms on 20170430
 */

#include "Storage/Reference.h"
#include <gtest/gtest.h>

using namespace Cyclone::Virtual;



class _Reference : public testing::Test
{
    protected:

        Reference _r0;
        Reference _r1;
        Reference _r2;
        
        _Reference(): 
            _r1( ((ulong)1 << 56) | ((ulong)4 << 48) | ((ulong)3 << 40) ),
            _r2(0, 1, 5, 2048)
        {

        }
};



/** CONSTRUCTORS **/
TEST_F(_Reference, Construction)
{
    ASSERT_EQ(_r0.Storage(),        0);
    ASSERT_EQ(_r0.Slot(),           0);
    ASSERT_EQ(_r0.Type(),           ReferenceTypes::Null);
    ASSERT_EQ(_r0.Offset(),         0);

    ASSERT_EQ(_r1.Storage(),        1);
    ASSERT_EQ(_r1.Slot(),           4);
    ASSERT_EQ(_r1.Type(),           ReferenceTypes::Number);
    ASSERT_EQ(_r1.Offset(),         0);

    ASSERT_EQ(_r2.Storage(),        0);
    ASSERT_EQ(_r2.Slot(),           1);
    ASSERT_EQ(_r2.Type(),           ReferenceTypes::Reference);
    ASSERT_EQ(_r2.Offset(),         2048);
}



/** OPERATORS **/
TEST_F(_Reference, EqualityOperators)
{
    ASSERT_EQ(_r1,                  _r1);
    ASSERT_EQ(_r2,                  _r2);
    ASSERT_NE(_r1,                  _r2);
}