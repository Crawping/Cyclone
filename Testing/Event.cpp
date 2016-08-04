/* CHANGELOG
 * Written by Josh Grooms on 20160804
 */

#include <gtest/gtest.h>
#include "Event.h"

using namespace Cyclone::Utilities;



class _Event : public ::testing::Test
{
    protected:
        int _number;
        //Action      _a1;
        //Event<int>  _e1;


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
void NumberFunction(int num1, int num2, int num3)
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

        void NumberMethod(int num1, int num2, int num3)
        {
            Number += (num1 + num2 + num3);
        }
};




/** TESTS **/
TEST_F(_Event, FunctionPointerInvocation)
{
    PlainFunctionPointer<> _f1 = PlainFunctionPointer<>(NumberFunction);
    _f1.Invoke();
    ASSERT_EQ(Number, 1);
    
    PlainFunctionPointer<int> _f2 = PlainFunctionPointer<int>(NumberFunction);
    _f2.Invoke(2);
    ASSERT_EQ(Number, 3);

    PlainFunctionPointer<int, int, int> _f3 = PlainFunctionPointer<int, int, int>(NumberFunction);
    _f3.Invoke(-5, 3, -1);
    ASSERT_EQ(Number, 0);
}

TEST_F(_Event, MethodPointerInvocation)
{
    NumberClass _c1 = NumberClass();
    ObjectMethodPointer<NumberClass> _m1 = ObjectMethodPointer<NumberClass>(&_c1, &NumberClass::NumberMethod);
    _m1.Invoke();
    ASSERT_EQ(_c1.Number, 1);

    ObjectMethodPointer<NumberClass, int> _m2 = ObjectMethodPointer<NumberClass, int>(&_c1, &NumberClass::NumberMethod);
    _m2.Invoke(2);
    ASSERT_EQ(_c1.Number, 3);

    ObjectMethodPointer<NumberClass, int, int, int> _m3 = ObjectMethodPointer<NumberClass, int, int, int>(&_c1, &NumberClass::NumberMethod);
    _m3.Invoke(-5, 3, -1);
    ASSERT_EQ(_c1.Number, 0);
}


//
//TEST_F(_Event, ActionFunctionCallback)
//{
//    //_a1 += PlainFunctionPointer<>(ComputeNumber);
//    _e1.Register(ComputeNumber);
//}