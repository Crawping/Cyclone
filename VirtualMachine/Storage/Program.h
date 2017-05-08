/* CHANGELOG
 * Written by Josh Grooms on 20170505
 */

#pragma once
#include "Virtual/Function.h"



namespace Cyclone
{
    namespace Virtual
    {
        class Program
        {
            public:

                const Function& Main() const { return _main; }

            private:
                
                Function _main;

        };
    }
}
