#include "Console.h"
#include "Utilities.h"
#include <iostream>
#include <string>

using std::cout;



namespace Cyclone
{
    namespace Utilities
    {
        namespace Console
        {
            void PostGeneralInfo(const string& file, int line, const string& msg)
            {
                string fileName = file.substr(file.find_last_of("\\/") + 1);
                WriteLine("INFO (" + fileName + " " + num2str(line) + "): " + msg);
            }
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
