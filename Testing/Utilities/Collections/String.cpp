/* CHANGELOG
 * Written by Josh Grooms on 20170502
 */

#include "Collections/String.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



class _String : public testing::Test
{
	protected:
		
		std::string		_ss1;

		String			_s0;
		String			_s1;
		String			_s2;


		_String():
			_ss1("Testing"),
			_s1("Testing")
		{
			_s2 = _s1;
		}
};



/** CONSTRUCTION **/
TEST_F(_String, Construction)
{
    constexpr String s1 = "Testing";
    constexpr uint c1 = s1.Count();

    ASSERT_EQ(c1,               _ss1.size());

	ASSERT_EQ(_s0.Count(),		0);
	ASSERT_EQ(_s1.Count(),		_ss1.size());
}




/** UTILITIES **/
TEST_F(_String, Indexing)
{
	for (uint a = 0; a < _ss1.size(); a++)
		ASSERT_EQ(_s1(a),		_ss1[a]);
}