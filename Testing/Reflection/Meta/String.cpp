/* CHANGELOG
 * Written by Josh Grooms on 20170424
 */

#include "Meta/String.h"
#include <gtest/gtest.h>

using namespace Cyclone::Reflection;
using namespace Cyclone::Utilities;



class _String : public testing::Test 
{
    protected:

        String _s1;


        _String() :
            _s1("Testing")
        {

        }

};



TEST_F(_String, Construction)
{
    ASSERT_EQ(_s1.Count(),  7);
}