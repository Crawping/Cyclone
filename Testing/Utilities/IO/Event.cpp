/* CHANGELOG
 * Written by Josh Grooms on 20160804
 */

#include "IO/Event.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



/** INTERNAL FUNCTIONS **/
static double Number = 0;
static void NumberFunction()                                    { Number += 1; }
static void NumberFunction(int num)                             { Number += num; }
static void NumberFunction(int num1, float num2, double num3)   { Number += (num1 + num2 + num3); }

class NumberClass
{
    public:
        double Number;

        NumberClass() : Number(0) { }

        void NumberMethod(void)                                 { Number += 1; }
        void NumberMethod(int num)                              { Number += num; }
        void NumberMethod(int num1, float num2, double num3)    { Number += (num1 + num2 + num3); }
};

class _Event : public ::testing::Test
{
    protected:
        
        NumberClass                         _c0;

        Action                              _a1;
        Event<int>                          _e1;
        Event<int, float, double>           _e2;

        Subscription<int>                   _s1;
        Subscription<int>                   _s2;
        Subscription<int, float, double>    _s3;
        Subscription<int, float, double>    _s4;


        _Event()
        {
            _a1.Subscribe(Function<void>(NumberFunction));
            _a1.Subscribe(&_c0, &NumberClass::NumberMethod);

            _s1 = _e1.Subscribe(NumberFunction);
            _s2 = _e1.Subscribe(&_c0, &NumberClass::NumberMethod);
            _s3 = _e2.Subscribe(NumberFunction);
            _s4 = _e2.Subscribe(&_c0, &NumberClass::NumberMethod);
        }
};



/** TESTS **/
TEST_F(_Event, Actions)
{
	_a1(); _a1();
	ASSERT_EQ(Number,       2);
    ASSERT_EQ(_c0.Number,   2);
}
TEST_F(_Event, Execution)
{
    Number = 0;

    _e1(10); _e1(20); _e1(-50);
    ASSERT_EQ(Number,       -20);
    ASSERT_EQ(_c0.Number,   Number);

    Number = 0;
    _c0.Number = 0;

    _e2(2, -4.8f, 3.14159);
    ASSERT_EQ(Number, 2 - 4.8f + 3.14159);
    ASSERT_DOUBLE_EQ(_c0.Number, Number);
}
TEST_F(_Event, Suspend)
{
    Number = 0;

    _s1.Suspend();
    _e1(10);
    ASSERT_EQ(Number, 0);
    ASSERT_EQ(_c0.Number, 10);

    _s1.Resume();
    _e1(10);
    ASSERT_EQ(Number, 10);
    ASSERT_EQ(_c0.Number, 20);
}
TEST_F(_Event, Unsubscribe)
{
    Number = 0;

    _s1.Cancel();
    _e1(10);
    ASSERT_EQ(Number, 0);
    ASSERT_EQ(_c0.Number, 10);

    _s2.Cancel();
    _e1(10);
    ASSERT_EQ(Number, 0);
    ASSERT_EQ(_c0.Number, 10);
}
