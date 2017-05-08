/* CHANGELOG
 * Written by Josh Grooms on 20170502
 */

#include "Primitives/Array.h"
#include <gtest/gtest.h>

using namespace Cyclone::Virtual;



class _Array : public testing::Test 
{
	protected:
		
        Array               _a0;
        Array               _a1;

        Reference           _i1;

        Vector<Number, 5>   _v1;


		_Array():
            _i1(0, 0, ReferenceTypes::Number, 0),
            _v1({ 0, 10, 20, 30, 40 })
		{
            _a1.Insert(_i1, _v1);
		}

};



/** CONSTRUCTION **/
TEST_F(_Array, Construction)
{
    ASSERT_EQ(_a0.Count(),          0);
    ASSERT_EQ(_a1.Count(),          _v1.Count());
}



/** UTILITIES **/
TEST_F(_Array, Insertion)
{
    for (uint a = 0; a < _v1.Count(); a++)
        ASSERT_EQ(_a1.Access(Reference(a)), Number(a * 10));
}