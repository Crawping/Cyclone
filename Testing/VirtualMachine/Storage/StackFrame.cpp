/* CHANGELOG
* Written by Josh Grooms on 20170501
*/

#include "Utilities.h"
#include "Storage/StackFrame.h"
#include <gtest/gtest.h>

using namespace Cyclone::VM;
using namespace Cyclone::VM::Virtual;



class _StackFrame : public testing::Test
{
    protected:

        StackFrame  _f0;
        Reference   _r1;
        Reference   _r2;
        Reference   _r3;
        String      _s1;        



        _StackFrame():
            _r1(1, 1, ReferenceTypes::Reference, 1),
            _r2(1, 0, ReferenceTypes::String, 1),
            _r3(0, 0, ReferenceTypes::String, hash("TestString")),
            _s1("Testing This Out")
        {
            _f0.Insert(_r1, _r2);
            _f0.Insert(_r2, _s1);
        }

};



/** CONSTRUCTORS **/
TEST_F(_StackFrame, Construction)
{

}



/** UTILITIES **/
TEST_F(_StackFrame, Access)
{
    ASSERT_EQ(_f0.Access<Reference>(_r1),   _r2);
    ASSERT_EQ(_f0.Access<String>(_r2),      _s1);
}



