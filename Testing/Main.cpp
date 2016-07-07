/* CHANGELOG
 * Written by Josh Grooms on 20160706
 */

#include "gtest/gtest.h"
#include <iostream>


//#include "_Color4.cpp"


__declspec(dllexport) int PullInMyLibrary() { return 0; }


int main(int nargs, char** args)
{
    static int notused = PullInMyLibrary();

    ::testing::InitGoogleTest(&nargs, args);
    return RUN_ALL_TESTS();
}