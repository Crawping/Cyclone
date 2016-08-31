/* CHANGELOG
 * Written by Josh Grooms on 20160830
 */

#include "Utilities.h"
#include "Math/Vector3.h"
#include <gtest/gtest.h>

using namespace Cyclone::Utilities;



TEST(Math, CrossProduct)
{
	EXPECT_EQ(Vector3::UnitZ, Math::Cross(Vector3::UnitX, Vector3::UnitY));

	Vector3 a(2.4f, 8.16f, -1024.128f);
	Vector3 b(-32.16, 512.256f, -64.64);
	Vector3 c(Math::Cross(a, b));
	Vector3 canon = Vector3(5.24088250368f, 0.3309109248f, 0.0149184f) * 1e5;

	EXPECT_FLOAT_EQ(canon.X, c.X);
	EXPECT_FLOAT_EQ(canon.Y, c.Y);
	EXPECT_FLOAT_EQ(canon.Z, c.Z);
}