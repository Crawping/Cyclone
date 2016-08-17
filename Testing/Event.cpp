/* CHANGELOG
 * Written by Josh Grooms on 20160804
 */

#include <gtest/gtest.h>
#include "Event.h"

using namespace Cyclone::Utilities;



class _Event : public ::testing::Test
{
    protected:
        int			_number;
        Action      _a1;
        Event<int>  _e1;


        _Event() : 
            _number(0)
        {

        }



        
};


/** INTERNAL FUNCTIONS **/
static int Number = 0;
void NumberFunction()
{
    Number += 1;
}
void NumberFunction(int num)
{
    Number += num;
}
void NumberFunction(int num1, float num2, double num3)
{
    Number += (num1 + num2 + num3);
}

class NumberClass
{
    public:
        int Number;

        NumberClass() : Number(0) { }

        void NumberMethod(void)
        {
            Number += 1;
        }

        void NumberMethod(int num)
        {
            Number += num;
        }

        void NumberMethod(int num1, float num2, double num3)
        {
            Number += (num1 + num2 + num3);
        }
};




/** TESTS **/
TEST_F(_Event, FunctionPointerInvocation)
{
    FunctionPointer<> _f1 = FunctionPointer<>(NumberFunction);
    _f1.Invoke();
    ASSERT_EQ(Number, 1);
    
    FunctionPointer<int> _f2 = FunctionPointer<int>(NumberFunction);
    _f2.Invoke(2);
    ASSERT_EQ(Number, 3);

    FunctionPointer<int, float, double> _f3 = FunctionPointer<int, float, double>(NumberFunction);
    _f3.Invoke(-5, 3, -1);
    ASSERT_EQ(Number, 0);
}

TEST_F(_Event, MethodPointerInvocation)
{
    NumberClass _c1 = NumberClass();
    MethodPointer<NumberClass> _m1 = MethodPointer<NumberClass>(&_c1, &NumberClass::NumberMethod);
    _m1.Invoke();
    ASSERT_EQ(_c1.Number, 1);

    MethodPointer<NumberClass, int> _m2 = MethodPointer<NumberClass, int>(&_c1, &NumberClass::NumberMethod);
    _m2.Invoke(2);
    ASSERT_EQ(_c1.Number, 3);

    MethodPointer<NumberClass, int, float, double> _m3 = MethodPointer<NumberClass, int, float, double>(&_c1, &NumberClass::NumberMethod);
    _m3.Invoke(-5, 3, -1);
    ASSERT_EQ(_c1.Number, 0);
}



TEST_F(_Event, ActionFunctionCallback)
{
    _a1.Register(NumberFunction);

	_a1(); _a1();
	ASSERT_EQ(Number, 2);
}

TEST_F(_Event, ActionMethodCallback)
{
    NumberClass _c1 = NumberClass();
    _a1.Register(&_c1, &NumberClass::NumberMethod);

    _a1(); _a1();
    ASSERT_EQ(_c1.Number, 2);
}


TEST_F(_Event, EventFunctionCallback)
{
    Number = 0;
    _e1.Register(NumberFunction);

    _e1(10); _e1(20); _e1(-50);
    ASSERT_EQ(Number, -20);
}

TEST_F(_Event, EventMethodCallback)
{
    NumberClass _c1 = NumberClass();
    _e1.Register(&_c1, &NumberClass::NumberMethod);

    _e1(10); _e1(20); _e1(-50);
    ASSERT_EQ(_c1.Number, -20);
}