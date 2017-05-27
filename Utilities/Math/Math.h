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
            /// <summary> Constrains numeric or comparable data to a range of values between some inputted minimum and maximum. </summary>
            /// <param name="x"> The data point to be constrained. </param>
            /// <param name="min"> The minimum value that <paramref name="x"/> is allowed to take. </param>
            /// <param name="max"> The maximum value that <paramref name="x"/> is allowed to take. </param>
            /// <returns> 
            ///     The same value of <paramref name="x"/> if it lies between <paramref name="min"/> and <paramref name="max"/>, 
            ///     inclusively. Otherwise, the closer of <paramref name="min"/> or <paramref name="max"/> is returned.
            /// </returns>
            template<typename T> constexpr T Clamp(T x, T min, T max)
            {
                return (x < min) ? min :
                    (x > max) ? max : x;
            }
            template<typename T> constexpr int Compare(const T& x, const T& y)
            {
                return (x < y) ? -1 :
                    (x > y) ? 1 : 0;
            }

            /// <summary> Returns the maximum of a list of values. </summary>
            template<typename T, typename ... U> constexpr T Max(T first, U ... values)
            {
                constexpr int N = sizeof...(U);
                const T vals[N] = { values... };

                T v = first;
                for (int a = 0; a < N; a++)
                    v = (vals[a] > v) ? vals[a] : v;

                return v;
            }
            /// <summary> Returns the minimum of a list of values. </summary>
            template<typename T, typename ... U> constexpr T Min(T first, U ... values)
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
