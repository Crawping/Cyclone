/* CHANGELOG 
 * Written by Josh Grooms on 20161129
 */

#include "Collections/Registry.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _Registry : public testing::Test
{
    protected:

        Registry<int>       _r0;
        Registry<int>       _r1;

        List<RegistryKey<int>>   _k1;


        _Registry()
        {
            for (uint a = 0; a < 6; a++)
                _k1.Append(_r1.Register(a));
        }
};



/** CONSTRUCTION TESTS **/
TEST_F(_Registry, DefaultConstruction)
{
    ASSERT_EQ(_r0.Count(), 0);
}



/** UTILITY TESTS **/
TEST_F(_Registry, NodeInsertion)
{
    ASSERT_EQ(_r1.Count(), 6);

    auto k1 = _r1.Register(3);
    ASSERT_EQ(_r1.Count(), 6);
    ASSERT_EQ(k1, _k1(3));

    auto k2 = _r1.Register(-1);
    ASSERT_EQ(_r1.Count(), 7);
}
TEST_F(_Registry, NodeRemoval)
{
    ASSERT_EQ(_r1.Count(), 6);

    _r1.Remove(_k1(3));
    ASSERT_EQ(_r1.Count(), 5);
    ASSERT_FALSE(_r1.Contains(_k1(3)));
}

