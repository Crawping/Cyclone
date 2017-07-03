/* CHANGELOG
 * Written by Josh Grooms on 20150906
 */


#include "Utilities.h"
#include "Math/Vector3.h"
#include <fstream>
#include <sstream>

using std::ios;



namespace Cyclone
{
    namespace Utilities
    {
        /** INTERNAL UTILITIES **/
        static std::hash<string> Hash;



        /** GENERAL UTILITIES **/
        uint hash(const string& string)
        {
            return Hash(string);
        }
        int sub2ind(int nrows, int ncols, int a, int b)
        {
             return b * nrows + a;
        }



        /** IO UTILITIES **/
        string readfile(const string& filename)
        {
            std::ifstream file(filename);
            string content;
            if (file)
            {
                file.seekg(0, ios::end);
                content.resize(file.tellg());
                file.seekg(0, ios::beg);
                file.read(&content[0], content.size());
                file.close();
            }
            return content;
        }
    }
}
