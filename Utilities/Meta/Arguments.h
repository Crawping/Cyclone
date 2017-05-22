/* CHANGELOG 
 * Written by Josh Grooms on 20170521
 */

#pragma once



namespace Cyclone
{
    namespace Utilities
    {
        namespace Meta
        {

            template<typename ... T> struct Arguments 
            { 
                private:
                    template<typename T, typename ... U> struct RemoveFirst:    public Arguments<U...> { };


                public:

                    template<uint N> struct Remove:                             public RemoveFirst<T...>::Remove<N - 1> { };
                    template<> struct Remove<0>:                                public Arguments<T...> { };
            };

        }
    }
}
