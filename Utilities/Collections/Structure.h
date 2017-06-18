/* CHANGELOG
 * Written by Josh Grooms on 20170617
 */

#pragma once
#include "Collections/Array.h"
#include "Meta/List.h"



namespace Cyclone
{
    namespace Utilities
    {

        template<uint N> 
        constexpr Array<uint, N> cumsum(const Array<uint, N>& values)
        {
            Array<uint, N> output(values);
            for (uint a = 1; a < N; a++)
                output(a) = (output(a - 1) + output(a));
            return output;
        }
        template<typename ... T>
        constexpr auto cumsum(T ... values)
        {
            return cumsum(Array<uint, sizeof...(T)>({ values... }));
        }
              
        


        template<typename ... T> struct Structure 
        {

            using Types = Meta::List<T...>;

            constexpr const static uint Count       = Types::Count;
            constexpr const static auto Offsets     = cumsum(0U, sizeof(T)...);
            constexpr const static uint Size        = Types::Size;

            private:

                Array<byte, Size> _data;

                template<typename T, typename U> 
                constexpr static T Cast(U& value) { return reinterpret_cast<T>(std::addressof(value)); }

            public:

                constexpr Structure() { }
                Structure(T ... values)
                {
                    Array<byte*, Count> v = { Cast<byte*>(values)... };
                    for (uint a = 0; a < Count; a++)
                        std::copy( v(a), v(a) + Types::Sizes[a], &_data(Offsets(a)) );
                }


                template<uint N> auto Get()
                {
                    return *Cast< Types::Get<N>* >(_data(Offsets(N)));
                }
                template<uint N> Structure& Set(Types::Get<N> value)
                { 
                    byte* v1 = Cast<byte*>(value);
                    std::copy(v1, v1 + Types::Sizes[N], &_data(Offsets(N)));
                    return *this;
                }

        };



        
        



        
    }
}
