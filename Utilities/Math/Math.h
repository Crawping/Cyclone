/* CHANGELOG
 * Written by Josh Grooms on 20170526
 */

#pragma once




namespace Cyclone
{
    namespace Utilities
    {
        namespace Math
        {

            /// <summary> Returns the maximum of a list of values. </summary>
            template<typename T, typename ... U>
            constexpr T Max(T first, U ... values)
            {
                constexpr int N = sizeof...(U);
                const T vals[N] = { values... };

                T v = first;
                for (int a = 0; a < N; a++)
                    v = (vals[a] > v) ? vals[a] : v;

                return v;
            }
            /// <summary> Returns the minimum of a list of values. </summary>
            template<typename T, typename ... U>
            constexpr T Min(T first, U ... values)
            {
                constexpr int N = sizeof...(U);
                const T vals[N] = { values... };

                T v = first;
                for (int a = 0; a < N; a++)
                    v = (vals[a] < v) ? vals[a] : v;

                return v;
            }
            /// <summary> Returns the cumulative product of a list of values. </summary>
            /// <returns> The result of multiplying all inputted values together. </returns>
            /// <param name="first"> The first value of the list being multiplied. </param>
            /// <param name="...values"> Any number of other values to be multiplied with the first. </param>
            template<typename T, typename ... U> constexpr T Product(T first, U ... values)
            {
                constexpr int N = sizeof...(U);
                const T vals[N] = { values... };

                T v = first;
                for (int a = 0; a < N; a++)
                    v *= vals[a];

                return v;
            }
            template<typename T> constexpr T Product(T first) { return first; }

        }
    }
}
