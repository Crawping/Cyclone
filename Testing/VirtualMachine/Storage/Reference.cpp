/* CHANGELOG
 * Written by Josh Grooms on 20170430
 */

#include "Storage/Reference.h"
#include <gtest/gtest.h>

using namespace Cyclone::VM::Virtual;



class _Reference : public testing::Test
{
    protected:

        Reference _a1;
        Reference _a2;
        
        _Reference(): 
            _a1( ((ulong)1 << 56) | ((ulong)4 << 48) | ((ulong)3 << 40) ),
            _a2(0, 1, 5, 2048)
        {

        }
};



/** CONSTRUCTORS **/
TEST_F(_Reference, Construction)
{
    ASSERT_EQ(_a1.Storage(),        1);
    ASSERT_EQ(_a1.Slot(),           4);
    ASSERT_EQ(_a1.Type(),           ReferenceTypes::Number);
    ASSERT_EQ(_a1.Offset(),         0);

    ASSERT_EQ(_a2.Storage(),        0);
    ASSERT_EQ(_a2.Slot(),           1);
    ASSERT_EQ(_a2.Type(),           ReferenceTypes::Reference);
    ASSERT_EQ(_a2.Offset(),         2048);
}



/** OPERATORS **/
TEST_F(_Reference, EqualityOperators)
{
    ASSERT_EQ(_a1,                  _a1);
    ASSERT_EQ(_a2,                  _a2);
    ASSERT_NE(_a1,                  _a2);
}