#include <iostream>
#include <string>
#include "Console.h"

using std::cout;



namespace Cyclone
{
    namespace Utilities
    {
        namespace Console
        {
            void Write(const string& msg)
            {
                cout << msg;
            }
            void Write(const char* msg)
            {
                cout << msg;
            }
            void WriteLine(const string& msg)
            {
                cout << msg << std::endl;
            }
            void WriteLine(const char* msg)
            {
                cout << msg << std::endl;
            }
        }
    }
}