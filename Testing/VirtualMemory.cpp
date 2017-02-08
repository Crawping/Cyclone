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

        Vector<int, 6>      _i1 = 0;
        Vector<string, 6>   _s1 = { "Variable0", "Variable1", "Variable2", "Variable3", "Variable4", "Variable5" };
        Vector<int, 6>      _v1 = { 0, 10, 20, 30, 40, 50 };

        VirtualClass        _c1;
        VirtualClass        _c2;
        VirtualProperty     _p1;

        VirtualMemory       _t0;
        VirtualMemory       _t1;

        _VirtualMemory() 
        {
            for (uint a = 0; a < _v1.Count(); a++)
            {
                _i1(a) = _t1.Insert(_s1(a));
                _t1.SetVariable(_i1(a), _v1(a));
            }

            _c1 = VirtualClass(_i1(1));
            _c2 = VirtualClass(_i1(2));
            _p1 = VirtualProperty(_i1(2), VariableTypes::Integer);
            _c1.Insert(_p1);
            _c2.Insert(_p1);

            _t1.Insert(_c1);
            _t1.Insert(_c2);
            _t1.SetObject(_c1.ID(), _p1.ID(), _i1(3), _v1(3));
            _t1.SetObject(_c2.ID(), _p1.ID(), _i1(4), _v1(4));
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
    ASSERT_EQ(_t1.ClassCount(), 2);

    ASSERT_NE(_v1(3), _v1(4));
    ASSERT_NE(_c1.ID(), _c2.ID());
    ASSERT_EQ(_t1.GetObject(_c1.ID(), _p1.ID(), _i1(3)), _v1(3));
    ASSERT_EQ(_t1.GetObject(_c2.ID(), _p1.ID(), _i1(4)), _v1(4));

    _t1.SetObject(_c2.ID(), _p1.ID(), _i1(4), _v1(5));
    ASSERT_NE(_t1.GetObject(_c2.ID(), _p1.ID(), _i1(4)), _v1(4));
    ASSERT_EQ(_t1.GetObject(_c2.ID(), _p1.ID(), _i1(4)), _v1(5));
}
TEST_F(_VirtualMemory, StringHashing)
{
    uint id = _i1(0);
    ASSERT_EQ(_t1.Find(id), _s1(0));
    ASSERT_EQ(_t1.Find(_s1(0)), id);

    for (uint a = 1; a < _i1.Count(); a++)
    {
        ASSERT_NE(_i1(a), id);
        ASSERT_EQ(_t1.Find(_i1(a)), _s1(a));
        ASSERT_EQ(_t1.Find(_s1(a)), _i1(a));
        id = _i1(a);
    }
}
TEST_F(_VirtualMemory, VariableDeletion)
{
    ASSERT_EQ(_t1.VariableCount(), _v1.Count());
    for (uint a = 0; a < _v1.Count(); a++)
    {
        _t1.DeleteVariable(_i1(a));
        ASSERT_EQ(_t1.VariableCount(), _v1.Count() - a - 1);
        ASSERT_EQ(_t1.GetVariable(_i1(a)), VirtualVariable());
    }
}
TEST_F(_VirtualMemory, VariableInsertion)
{
    ASSERT_EQ(_t1.VariableCount(), _v1.Count());
    for (uint a = 0; a < _v1.Count(); a++)
        ASSERT_EQ(_t1.GetVariable(_i1(a)), _v1(a));
}
