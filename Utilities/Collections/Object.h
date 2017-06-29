/* CHANGELOG
 * Written by Josh Grooms on 20170628
 */

#pragma once
#include "Collections/Array.h"
#include "IO/Property.h"
#include "Meta/Array.h"
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


        template<typename ... T> struct Object { };
        //struct IObject { };

        template<typename T, typename ... U> 
        struct Object<T, U...>
        {

            using Types                         = Meta::List<T, U...>;
            constexpr const static uint Count   = Types::Count;

            private:

                T               _value;
                Object<U...>    _fields;

            public:

                /** CONSTRUCTORS **/
                constexpr Object():
                    _value{ },
                    _fields{ }
                {

                }

                constexpr Object(T value, U ... fields):
                    _value(value),
                    _fields(fields...)
                {

                }

                template<uint N> constexpr static auto Attribute()
                {
                    return Utilities::Attribute<Object, Types::Get<N>>
                    (
                        &Object::Get<N>,
                        &Object::Set<N, Types::Get<N>>
                    );
                }
                template<uint N> constexpr auto Get()               const { return _fields.Get<N - 1>(); }
                template<> constexpr auto Get<0>()                  const { return _value; }
                template<uint N, typename V> Object& Set(V value)
                {
                    _fields.Set<N - 1>(value);
                    return *this;
                }
                template<> Object& Set<0, T>(T value)
                {
                    _value = value;
                    return *this;
                }
                template<uint N> auto Property()
                {
                    return Utilities::Property<Object, Types::Get<N>>
                    (
                        this,
                        &Object::Get<N>,
                        &Object::Set<N, Types::Get<N>>
                    );
                }
        };

        template<> struct Object<>
        {
            using Types = Meta::List<>;

            constexpr const static uint Count   = Types::Count;
            constexpr const static uint Size    = Types::Size;

            Object() { }


            template<uint N> constexpr static auto Attribute()
            {
                return Utilities::Attribute<Object, Types::Get<N>>
                (
                    &Object::Get<N>,
                    &Object::Set<N>
                );
            }

            template<uint N> constexpr auto Get() const
            {
                //return _value;
                return nullptr;
            }
            template<uint N, typename T> Object& Set(T value)
            {
                //_value = value;
                return *this;
            }


        };

    }
}
