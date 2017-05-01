/* CHANGELOG
 * Written by Josh Grooms on 20170430
 */

#include "Storage/Address.h"
#include <gtest/gtest.h>

using namespace Cyclone::VM::Virtual;



class _Address : public testing::Test
{
    protected:

        Reference _a1;
        
        _Address(): 
            _a1( ((ulong)1 << 56) | ((ulong)4 << 48) | ((ulong)3 << 40) )
        {

        }
};



TEST_F(_Address, Construction)
{
    ASSERT_EQ(_a1.Storage(),        1);
    ASSERT_EQ(_a1.Slot(),           4);
    ASSERT_EQ(_a1.Type(),           ReferenceTypes::Number);
    ASSERT_EQ(_a1.Offset(),         0);
}