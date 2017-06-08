/* CHANGELOG
 * Written by Josh Grooms on 20170107
 */

#include "IO/Functions.h"
#include "IO/Members.h"
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
        double _number;

        double Number()                     { return _number; }
        NumberClass& Number(double value)   { _number = value; return *this; }

        NumberClass() : _number(0) { }

        void NumberMethod(void)                                 { _number += 1; }
        void NumberMethod(int num)                              { _number += num; }
        void NumberMethod(int num1, float num2, double num3)    { _number += (num1 + num2 + num3); }
};



class _Functions : public testing::Test
{
    protected:

        NumberClass                                     _c0;

        Procedure<>                                     _f1;
        Procedure<int>                                  _f2;
        Procedure<int, float, double>                   _f3;

        Method<void, NumberClass>                       _m1;
        Method<void, NumberClass, int>                  _m2;
        Method<void, NumberClass, int, float, double>   _m3;

        Method<double, NumberClass>                     _m4;
        Method<NumberClass&, NumberClass, double>       _m5;

        Property<double, NumberClass, double>           _p1;
        

        _Functions() :
            _f1(NumberFunction),
            _f2(NumberFunction),
            _f3(NumberFunction),
            _m1(&_c0, &NumberClass::NumberMethod),
            _m2(&_c0, &NumberClass::NumberMethod),
            _m3(&_c0, &NumberClass::NumberMethod),
            _m4(&_c0, &NumberClass::Number),
            _m5(&_c0, &NumberClass::Number),
            _p1(&_c0, &NumberClass::Number, &NumberClass::Number)
        {

        }
};



/** OPERATOR TESTS **/
TEST_F(_Functions, EqualityOperator)
{
    ASSERT_TRUE(_f1 == _f1);
    ASSERT_TRUE(_m1 == _m1);

    Procedure<int> fcn = Procedure<int>(NumberFunction);
    ASSERT_EQ(_f2, fcn);

    Method<void, NumberClass, int> mtd = Method<void, NumberClass, int>(&_c0, &NumberClass::NumberMethod);
    ASSERT_EQ(_m2, mtd);
}
TEST_F(_Functions, FunctionPointerInvocation)
{
    _f1.Invoke();
    ASSERT_EQ(Number, 1);

    _f2.Invoke(2);
    ASSERT_EQ(Number, 3);

    _f3.Invoke(-5, 3, -1);
    ASSERT_EQ(Number, 0);
}
TEST_F(_Functions, MethodPointerInvocation)
{
    _m1.Invoke();
    ASSERT_EQ(_c0._number, 1);

    _m2.Invoke(2);
    ASSERT_EQ(_c0._number, 3);

    _m3.Invoke(-5, 3, -1);
    ASSERT_EQ(_c0._number, 0);
}
TEST_F(_Functions, Properties)
{
    _m1.Invoke();
    ASSERT_EQ(_c0._number, 1);
    ASSERT_EQ(_p1.Invoke(), 1);

    _p1.Invoke(2);
    ASSERT_EQ(_c0._number, 2);
    ASSERT_EQ(_p1.Invoke(), 2);
    ASSERT_EQ(_p1(), 2);

    _p1(_p1() + _p1());
    ASSERT_EQ(_p1(), 4);
}





