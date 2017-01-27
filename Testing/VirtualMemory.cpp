/* CHANGELOG
 * Written by Josh Grooms on 20170122
 */

#include "TypeDefinitions.h"
#include "Storage/VirtualMemory.h"
#include <gtest/gtest.h>

using namespace Cyclone::VM;
using namespace Cyclone::Utilities;



class _VirtualMemory : public testing::Test
{
    protected:

        Vector<int, 5>      _i1 = 0;
        Vector<string, 5>   _s1 = { "Variable0", "Variable1", "Variable2", "Variable3", "Variable4" };
        Vector<int, 5>      _v1 = { 0, 10, 20, 30, 40, 50 };

        VirtualClass        _c1;
        VirtualProperty     _p1;

        VirtualMemory       _t0;
        VirtualMemory       _t1;

        _VirtualMemory() 
        {
            for (uint a = 0; a < _v1.Count(); a++)
            {
                _i1(a) = _t1.Insert(_s1(a));
                _t1.Set(_i1(a), _v1(a));
            }

            _c1 = VirtualClass(_i1(1));
            _p1 = VirtualProperty(_i1(2));
            _c1.Insert(_p1);

            _t1.Insert(_c1);
            _t1.Set(_c1.ID(), _p1.ID(), _i1(3), _v1(3));
        }

};



/** CONSTRUCTION TESTS **/
TEST_F(_VirtualMemory, DefaultConstruction)
{
    ASSERT_EQ(_t0.ClassCount(),     0);
    ASSERT_EQ(_t0.FunctionCount(),  0);
    ASSERT_EQ(_t0.VariableCount(),  0);
}



/** UTILITY TESTS **/
TEST_F(_VirtualMemory, ClassInsertion)
{
    ASSERT_EQ(_t1.Get(_i1(1)), _v1(1));
    ASSERT_EQ(_t1.Get(_c1.ID(), _p1.ID(), _i1(3)), _v1(3));
}
TEST_F(_VirtualMemory, StringHashing)
{
    uint id = _i1(0);
    ASSERT_EQ(_t1.FindName(id), _s1(0));
    ASSERT_EQ(_t1.FindID(_s1(0)), id);

    for (uint a = 1; a < _i1.Count(); a++)
    {
        ASSERT_NE(_i1(a), id);
        ASSERT_EQ(_t1.FindName(_i1(a)), _s1(a));
        ASSERT_EQ(_t1.FindID(_s1(a)), _i1(a));
        id = _i1(a);
    }
}
TEST_F(_VirtualMemory, VariableDeletion)
{
    ASSERT_EQ(_t1.VariableCount(), _v1.Count());
    for (uint a = 0; a < _v1.Count(); a++)
    {
        _t1.Delete(_i1(a));
        ASSERT_EQ(_t1.VariableCount(), _v1.Count() - a - 1);
        ASSERT_EQ(_t1.Get(_i1(a)),  Literal());
    }
}
TEST_F(_VirtualMemory, VariableInsertion)
{
    ASSERT_EQ(_t1.VariableCount(), _v1.Count());
    for (uint a = 0; a < _v1.Count(); a++)
        ASSERT_EQ(_t1.Get(_i1(a)), _v1(a));
}
