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
        /** ARRAY UTILITIES **/
        int sub2ind(int nrows, int ncols, int a, int b)
        {
             return b * nrows + a;
        }
        uint nextpow2(uint x)
        {
            uint y = x - 1;
            y |= y >> 1;
            y |= y >> 2;
            y |= y >> 4;
            y |= y >> 8;
            y |= y >> 16;

            return y + 1;
        }




        /** MATH UTILITIES **/
        namespace Math
        {
			constexpr Vector3 Cross(const Vector3& u, const Vector3& v)
			{
				return Vector3
				(
					(u.Y * v.Z) - (u.Z * v.Y),
					(u.Z * v.X) - (u.X * v.Z),
					(u.X * v.Y) - (u.Y * v.X)
				);
			}
            constexpr float Max(float x, float y, float z)
            {
                return  (x > y) ?
                            ((x > z) ? x : z) :
                            ((y > z) ? y : z);
            }
            constexpr float Max(float x, float y, float z, float w)
            {
                return  (x > y) ?
                            (x > z) ?
                                ((x > w) ? x : w) :
                                ((z > w) ? z : w) :
                            (y > z) ?
                                ((y > w) ? y : w) :
                                ((z > w) ? z : w);
            }
            constexpr float Min(float x, float y, float z)
            {
                return  (x < y) ?
                            ((x < z) ? x : z ) :
                            ((y < z) ? y : z );
            }
            constexpr float Min(float x, float y, float z, float w)
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
    }
}
