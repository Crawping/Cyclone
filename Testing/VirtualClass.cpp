/* CHANGELOG
 * Written by Josh Grooms on 20170206
 */

#include "Storage/VirtualClass.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;
using namespace Cyclone::VM;



class _VirtualClass : public testing::Test
{
    protected:

        Vector<int, 5> propIDs          = { 1, 2, 3, 4, 5 };
        Vector<string, 5> propNames     = { "Components", "Geometry", "IsVisible", "Material", "Transforms" };
        

        VirtualClass _c0;
        VirtualClass _c1;



        _VirtualClass() : 
            _c1(1)
        {
            for (int id : propIDs)
                _c1.Insert(VirtualProperty(id, { VariableTypes::Integer }));
        }
};



/** CONSTRUCTION TESTS **/
TEST_F(_VirtualClass, DefaultConstruction)
{
    ASSERT_EQ(_c0.ID(),             0);
    ASSERT_EQ(_c0.InstanceCount(),  0);
    ASSERT_EQ(_c0.MethodCount(),    0);
}

TEST_F(_VirtualClass, PropertyInsertion)
{
    ASSERT_EQ(_c1.ID(),             1);
    ASSERT_EQ(_c1.InstanceCount(),  0);
    ASSERT_EQ(_c1.MethodCount(),    0);
    ASSERT_EQ(_c1.PropertyCount(),  propIDs.Count());
}

TEST_F(_VirtualClass, Instancing)
{
    _c1.Set(1, 1, 10);
    ASSERT_EQ(_c1.InstanceCount(), 1);

    _c1.Set(2, 1, 20);
    ASSERT_EQ(_c1.InstanceCount(), 2);

    _c1.Set(3, 1, 30);
    ASSERT_EQ(_c1.InstanceCount(), 3);

    ASSERT_EQ(_c1.Get(1, 1), 10);
    ASSERT_EQ(_c1.Get(2, 1), 20);
    ASSERT_EQ(_c1.Get(3, 1), 30);
}