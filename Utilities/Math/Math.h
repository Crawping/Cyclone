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
            /// <summary> Rounds fractional values up to the next more positive integer. </summary>
            /// <returns> 
            ///     The next integral value higher than <paramref name="x"/>, or the value in <paramref name="x"/> 
            ///     if it is already integral.
            /// </returns>
            /// <param name="x"> The value to be rounded upward. </param>
            template<typename T> constexpr T Ceil(T x)
            {
                T y = Fix(x);
                return y + ( (x - y > 0) ? 1 : 0 );
            }
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
            /// <summary> Rounds fractional values toward zero. </summary>
            /// <param name="x"> The value to be rounded. </param>
            /// <returns> 
            ///     The next integral value closer to zero relative to <paramref name="x"/>, or the value in <paramref name="x"/> 
            ///     if it is already integral.
            /// </returns>
            template<typename T> constexpr T Fix(T x)           { return (T)(int64_t)x; }
            /// <summary> Rounds fractional values down to the next more negative integer. </summary>
            /// <param name="x"> The value to be rounded downward. </param>
            /// <returns> 
            ///     The next integral value lower than <paramref name="x"/>, or the value in <paramref name="x"/> 
            ///     if it is already integral.
            /// </returns>
            template<typename T> constexpr T Floor(T x)
            {
                T y = Fix(x);
                return y - ( (x - y < 0) ? 1 : 0 );
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
            /// <summary> Finds the next value greater than or equal to the input that is also an integral power of two. </summary>
            template<typename T> constexpr T NextPower2(T x)
            {
                int64_t y = Ceil(x) - 1;
                y |= y >> 1;
                y |= y >> 2;
                y |= y >> 4;
                y |= y >> 8;
                y |= y >> 16;

                return y + 1;
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
            /// <summary> Rounds fractional values to the nearest integer. </summary>
            /// <param name="x"> The value to be rounded. </param>
            /// <returns> 
            ///     The next integral value closest to <paramref name="x"/>, or the value in <paramref name="x"/> 
            ///     if it is already integral.
            /// </returns>
            template<typename T> constexpr T Round(T x)
            {
                T y = Fix(x);
                return y +
                (
                    (x - y <= -0.5) ? -1 :
                    (x - y >= 0.5) ? 1 : 0
                );
            }
            /// <summary> Returns the sign of a value. </summary>
            /// <returns> A <c>-1</c> if the value is less than zero, or <c>1</c> otherwise. </returns>
            /// <param name="x"> The value being tested. </param>
            template<typename T> constexpr int Sign(T x)        { return (x < 0) ? -1 : 1; }

            template<typename T> /*constexpr*/ T Sqrt(T x)
            {
                //int ix = *reinterpret_cast<int*>(&x);
                //ix = 0x5F375A86 - (ix >> 1);
                //T y = *reinterpret_cast<T*>(&ix);



                //T hx = 0.5 * x;
                //y = y * (1.5f - (hx * y * y));
                //y = y * (1.5f - (hx * y * y));

                //return y * x;

                float hx = 0.5f * x;
                union { T X; int I; } ux = { x };
                ux.I = 0x5F375A86 - (ux.I >> 1);

                ux.X = ux.X * (1.5f - hx * ux.X * ux.X);
                ux.X = ux.X * (1.5f - hx * ux.X * ux.X);
                ux.X = ux.X * (1.5f - hx * ux.X * ux.X);
                ux.X = ux.X * (1.5f - hx * ux.X * ux.X);
                ux.X = ux.X * (1.5f - hx * ux.X * ux.X);
                ux.X = ux.X * (1.5f - hx * ux.X * ux.X);
                ux.X = ux.X * (1.5f - hx * ux.X * ux.X);
                ux.X = ux.X * (1.5f - hx * ux.X * ux.X);

                return ux.X * x;



                //if (x == 0 || x == 1) return x;

                //T lower = 0, upper = (x / 2) + 1;
                //while (lower != upper)
                //{
                //    upper = (lower + upper + 1) / 2;
                //    T middle = (lower + upper + 1) / 2;
                //    if (middle > x / middle)
                //        upper = middle - 1;
                //    else
                //        lower = middle;
                //}

                //return lower;
            }
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
            /// <summary> Rounds fractional values away from zero. </summary>
            /// <param name="x"> The value to be rounded. </param>
            /// <returns>
            ///     The next integral value farther from zero relative to <paramref name="x"/>, or the value in <paramref name="x"/> 
            ///     if it is already integral.
            /// </returns>
            template<typename T> constexpr T Unfix(T x)
            {
                T y = Fix(x);
                return y +
                (
                    (x - y < 0) ? -1 :
                    (x - y > 0) ? 1 : 0
                );
            }
        }
    }
}
