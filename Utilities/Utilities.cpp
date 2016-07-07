/* CHANGELOG
 * Written by Josh Grooms on 20150906
 */


#include "Utilities.h"
#include <fstream>
#include <sstream>

using std::ios;



/** ARRAY UTILITIES **/
int sub2ind(int nrows, int ncols, int a, int b)
{
     return b * nrows + a;
}



/** MATH UTILITIES **/
namespace Math
{

    float Max(float x, float y, float z)
    {
        return  (x > y) ?
                    ((x > z) ? x : z) :
                    ((y > z) ? y : z);
    }
    float Max(float x, float y, float z, float w)
    {
        return  (x > y) ?
                    (x > z) ?
                        ((x > w) ? x : w) :
                        ((z > w) ? z : w) :
                    (y > z) ?
                        ((y > w) ? y : w) :
                        ((z > w) ? z : w);
    }
    float Min(float x, float y, float z)
    {
        return  (x < y) ?
                    ((x < z) ? x : z ) :
                    ((y < z) ? y : z );
    }
    float Min(float x, float y, float z, float w)
    {
        return  (x < y) ?
                    (x < z) ?
                        ((x < w) ? x : w) :
                        ((z < w) ? z : w) :
                    (y < z) ?
                        ((y < w) ? y : w) :
                        ((z < w) ? z : w);
    }
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








