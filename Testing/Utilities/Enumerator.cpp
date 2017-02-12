/* CHANGELOG
 * Written by Josh Grooms on 20160818
 */

#include "Enumerator.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



struct TestEnumerator : public Enumerator
{
	enum EnumValues
	{
		Value1,
		Value2,
		Value3,
	};


	TestEnumerator(enum EnumValues value = Value1) : Enumerator(value) { }
};

struct TestFlag : public Flag<TestFlag>
{
	enum FlagValues
	{
		Value1 = 1,
		Value2 = 2,
		Value3 = 4,		
	};

	TestFlag(enum FlagValues value = Value1) : Flag<TestFlag>(value) { }
    TestFlag(int value) : TestFlag((FlagValues)value) { }
};

struct AltFlag : public Flag<AltFlag>
{
	enum AltValues
	{
		Value1 = (1 << 3),
		Value2 = (1 << 4),
		Value3 = (1 << 5),
	};

	AltFlag(enum AltValues value = Value1) : Flag<AltFlag>(value) { }
};



class _Enumerator : public testing::Test
{
	protected:
		TestEnumerator _e0;
		TestEnumerator _e1;
		TestEnumerator _e2;
		TestEnumerator _e3;

		TestFlag		_f0;
		TestFlag		_f1;
		TestFlag		_f2;
		TestFlag		_f3;

		AltFlag			_a0;
		AltFlag			_a1;
		AltFlag			_a2;
		
		_Enumerator() :
			_e1(TestEnumerator::Value1),
			_e2(TestEnumerator::Value2),
			_e3(TestEnumerator::Value3),
			_f1(TestFlag::Value1),
			_f2(TestFlag::Value2),
			_f3(TestFlag::Value3),
			_a1(AltFlag::Value2),
			_a2(AltFlag::Value3)
		{

		}

};



TEST_F(_Enumerator, EnumConstruction)
{
	ASSERT_EQ(_e0, _e1);
	ASSERT_EQ(_e1, TestEnumerator::Value1);
	ASSERT_EQ(_e2, TestEnumerator::Value2);
	ASSERT_EQ(_e3, TestEnumerator::Value3);

	ASSERT_EQ(_e0, 0);
	ASSERT_EQ(_e1, 0);
	ASSERT_EQ(_e2, 1);
	ASSERT_EQ(_e3, 2);

	ASSERT_NE(_e1, _e2);
}

TEST_F(_Enumerator, FlagConstruction)
{
	ASSERT_EQ(_f0, _f1);
	ASSERT_EQ(_f1, TestFlag::Value1);
	ASSERT_EQ(_f2, TestFlag::Value2);
	ASSERT_EQ(_f3, TestFlag::Value3);

	ASSERT_EQ(_f0, 1);
	ASSERT_EQ(_f1, 1);
	ASSERT_EQ(_f2, 2);
	ASSERT_EQ(_f3, 4);

	ASSERT_NE(_f1, _f2);
}

TEST_F(_Enumerator, FlagOrOperators)
{
	TestFlag _f1Copy = TestFlag(_f1);
	_f1Copy |= _f3;

	ASSERT_NE(_f1, _f1Copy);
	ASSERT_EQ(_f1Copy, 1 | 4);
	ASSERT_EQ(_f1Copy, TestFlag::Value1 | TestFlag::Value3);

	// Does not compile
	//_f1Copy |= TestEnumerator::Value3;
	//_f1Copy |= 2;
	//_f1Copy = TestFlag::Value1 | TestFlag::Value3 | TestEnumerator::Value3 
	//TestFlag flag = TestFlag::Value1 | TestFlag::Value3 | TestEnumerator::Value3;

	// Does not compile
	//_f1Copy = _a1;
	//_f1Copy |= _a1;
	//_f1Copy = TestFlag::Value1 | AltFlag::Value1;

    TestFlag f1 = TestFlag::Value1 | TestFlag::Value3;

	AltFlag _a3 = _a0 | _a1;
	ASSERT_EQ(_a3, AltFlag::Value1 | AltFlag::Value2);

    _a3 |= _a0 | _a1 | _a2;
    ASSERT_EQ(_a3, AltFlag::Value1 | AltFlag::Value2 | AltFlag::Value3);


}