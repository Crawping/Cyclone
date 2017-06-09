/* CHANGELOG
 * Written by Josh Grooms on 20170425
 */

#pragma once
#include "IO/Functions.h"
#include "Meta/List.h"



namespace Cyclone
{
    namespace Utilities
    {
        namespace Meta
        {

            template<typename T> struct Functor                 { };
            template<typename T, typename ... U>
            struct Functor<FunctionPointer<T, U...>>:           public Class<FunctionPointer<T, U...>>
            {
                using Binding       = void;
                using Inputs        = List<U...>;
                using IsPointer     = Boolean<true>;
                using Output        = T;
            };

            template<typename T, typename U>
            struct Functor<MemberPointer<T, U>>:                public Class<MemberPointer<T, U>>
            { 
                using Binding       = U;
                using Inputs        = void;
                using IsPointer     = Boolean<true>;
                using Output        = T;
            };

            template<typename T, typename U, typename ... V>
            struct Functor<MethodPointer<T, U, V...>>:          public Class<MethodPointer<T, U, V...>>
            {
                using Binding       = U;
                using Inputs        = List<V...>;
                using IsPointer     = Boolean<true>;
                using Output        = T;
            };

            template<typename T, typename U, typename ... V>
            struct Functor<ConstMethodPointer<T, U, V...>>:     public Class<ConstMethodPointer<T, U, V...>>
            {
                using Binding       = U;
                using Inputs        = List<V...>;
                using IsPointer     = Boolean<true>;
                using Output        = T;
            };


            template<typename T, typename ... U>                using Function = Functor<FunctionPointer<T, U...>>;
            template<typename T, typename U>                    using Member = Functor<MemberPointer<T, U>>;
            template<typename T, typename U, typename ... V>    using Method = Functor<MethodPointer<T, U, V...>>;


            //template<typename T> struct InputTypes              { };
            //template<typename T, typename U, typename ... V>
            //struct InputTypes< MethodPointer<T, U, V...> >      { using Value = List<V...>; };

            //template<typename T> struct ReturnType              { };
            //template<typename T, typename U, typename ...V>
            //struct ReturnType< MethodPointer<T, U, V...> >      { using Value = T; };

            ////template<typename T, typename U>
            ////struct ReturnType<MemberPointer<T, U>>              { using };

            //template<typename T, typename ... U>
            //struct ReturnType< ICallback<T, U...> >             { using Value = T; };
        }
    }
}
