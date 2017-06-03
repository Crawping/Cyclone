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
            /// <summary> Returns the absolute value of the input. </summary>
            template<typename T> constexpr T Abs(T x) { return (x < 0) ? -x : x; }
            /// <summary> Constrains data to a range of values between some inputted minimum and maximum. </summary>
            /// <param name="x"> The value to be constrained. </param>
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
            /// <summary> Determines the ordering relationship between two values. </summary>
            /// <returns> 
            ///     A <c>-1</c> if <paramref name="x"/> is less than <paramref name="y"/>, a <c>0</c> if they are equal, 
            ///     or a <c>1</c> if <paramref name="x"/> is greater than <paramref name="y"/>.
            /// </returns>
            /// <param name="x"> The first value. </param>
            /// <param name="y"> The second value. </param>
            template<typename T> constexpr int Compare(T x, T y)
            {
                return (x < y) ? -1 :
                    (x > y) ? 1 : 0;
            }
            /// <summary> Determines whether a value lies within a range of values. </summary>
            /// <returns>
            ///     A Boolean <c>true</c> if <paramref name="x"/> lies between <paramrefname="min"/> and <paramref name="max"/>, 
            ///     or <c>false</c> otherwise.
            /// </returns>
            /// <param name="x"> The value to be tested. </param>
            /// <param name="min"> The lower bound of the range of values. </param>
            /// <param name="max"> The upper bound of the range of values. </param>
            /// <param name="inclusive"> An value of <c>true</c> if the bounds should be considered inside the range, or <c>false</c> otherwise. </param>
            template<typename T> constexpr bool IsBetween(T x, T min, T max, bool inclusive = true)
            {
                T lower = Min(min, max), upper = Max(min, max);
                return inclusive ? (x >= lower && x <= upper) :
                    (x > lower && x < upper);
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
            /// <summary> Returns the inputted value. </summary>
            /// <remarks> This function exists as a stop condition for the variadic template of the same name. </remarks>
            template<typename T> constexpr T Product(T first)   { return first; }
            /// <summary> Returns the sign of a value. </summary>
            /// <returns> A <c>-1</c> if the value is less than zero, or <c>1</c> otherwise. </returns>
            /// <param name="x"> The value being tested. </param>
            template<typename T> constexpr int Sign(T x)        { return (x < 0) ? -1 : 1; }
            /// <summary> Returns the cumulative sum of a list of values. </summary>
            /// <returns></returns>
            /// <param name="first"> The first value of the list being added. </param>
            /// <param name="...values"> Any number of other values to be added with the first. </param>
            template<typename T, typename ... U> constexpr T Sum(T first, U ... values)
            {
                constexpr int N = sizeof...(U);
                const T vals[N] = { values... };

                T v = first;
                for (int a = 0; a < N; a++)
                    v += vals[a];

                return v;
            }
            /// <summary> Returns the inputted value. </summary>
            /// <remarks> This function exists to prevent the variadic overload from trying to create empty arrays. </remarks>
            template<typename T> constexpr T Sum(T first)       { return first; }
        }
    }
}
