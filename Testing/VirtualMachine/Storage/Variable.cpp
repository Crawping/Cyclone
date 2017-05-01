/* CHANGELOG
 * Written by Josh Grooms on 20170429
 */

#include "Virtual/Variable.h"
#include <gtest/gtest.h>

using namespace Cyclone::VM;



class _Variable : public testing::Test
{
    protected:

        Virtual::Variable _v0;


        _Variable()
        {

        }
};


TEST_F(_Variable, Construction)
{
    ASSERT_EQ(_v0.Type(),       Virtual::ReferenceTypes::Null);
    ASSERT_EQ(_v0.Value(),      0);
}