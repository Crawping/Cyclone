/* CHANGELOG
 * Written by Josh Grooms on 20160706
 */

#include "gtest/gtest.h"
#include <iostream>



int main(int nargs, char** args)
{
    ::testing::InitGoogleTest(&nargs, args);
    return RUN_ALL_TESTS();
}