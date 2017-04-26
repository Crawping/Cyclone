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

        using S0 = Meta::String<>;
        using S1 = Meta::String<'T', 'e', 's', 't', 'i', 'n', 'g'>;
        using S2 = S1::Concatenate<' ', 'T', 'h', 'i', 's'>;

        String _s1;
        


        _String() :
            _s1("Testing")
        {

        }

};



TEST_F(_String, Construction)
{

    ASSERT_EQ(_s1.Count(),                  7);
    ASSERT_EQ(_s1.Value(),                  "Testing");
    ASSERT_NE(_s1,                          "testing");

    ASSERT_EQ(S0::Count(),                  0);
    ASSERT_EQ(S0::First(),                  NULL);
    ASSERT_EQ(S0::Last(),                   NULL);

    ASSERT_EQ(S1::Count(),                  7);
    ASSERT_EQ(S1::First(),                  'T');
    ASSERT_EQ(S1::Last(),                   'g');
    
    ASSERT_EQ(S1(),                         "Testing");
    ASSERT_NE(S1(),                         "testing");
    ASSERT_EQ(S1(),                         _s1);

    ASSERT_EQ(S1(),                         S1());
    ASSERT_NE(S1(),                         S2());
}
TEST_F(_String, Concatenation)
{
    auto s2 = S2();
    ASSERT_EQ(S2::Count(),                  12);
    ASSERT_EQ(s2,                           "Testing This");

    auto c = Meta::Character<'A'>();
    auto s3 = S2::Cat(c);

    ASSERT_EQ(s3(12),                       'A');

}
TEST_F(_String, Discarding)
{
    using S3 = S1::Discard;
    using S4 = S3::Discard;

    ASSERT_EQ(S3::Count(),                  6);
    ASSERT_EQ(S3::First(),                  'e');

    ASSERT_EQ(S4::Count(),                  5);
    ASSERT_EQ(S4::First(),                  's');
}
TEST_F(_String, Indexing)
{
    const string str = "Testing";
    ASSERT_EQ(str.length(), _s1.Count());

    for (uint a = 0; a < _s1.Count(); a++)
        ASSERT_EQ(_s1(a),                   str[a]);

    ASSERT_EQ(_s1(_s1.Count()),             NULL);
    ASSERT_EQ(_s1(_s1.Count()),             '\0');

    ASSERT_EQ(S1::Get<0>(),                 'T');
    ASSERT_EQ(S1::Get<6>(),                 'g');
    
    auto c1 = S1();
    for (uint a = 0; a < S1::Count(); a++)
        ASSERT_EQ(c1(a),                    _s1(a));
}