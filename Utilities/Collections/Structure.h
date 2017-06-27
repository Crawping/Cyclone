/* CHANGELOG
 * Written by Josh Grooms on 20170617
 */

#pragma once
#include "Collections/Array.h"
#include "IO/Property.h"
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
              
        


        struct IStructure {  };

        template<typename ... T> struct Structure: public IStructure
        {

            /// <summary> A list of the types that are stored in the structure. </summary>
            using Types = Meta::List<T...>;

            /// <summary> The number of data fields in the structure. </summary>
            constexpr const static uint Count       = Types::Count;
            /// <summary> The byte offsets of the data fields in the structure. </summary>
            constexpr const static auto Offsets     = cumsum(0U, sizeof(T)...);
            /// <summary> The total size of one structure instance in bytes. </summary>
            constexpr const static uint Size        = Types::Size;

            private:

                Array<byte, Size> _data;

                /// <summary> Performs a reinterpret-cast operation. </summary>
                template<typename U, typename V> static U Cast(V& value)
                {
                    return reinterpret_cast<U>( std::addressof(value) );
                }

            public:

                /** CONSTRUCTORS **/
                /// <summary> Creates a new data structure instance whose fields are uninitialized. </summary>
                Structure() { }
                /// <summary> Constructs a new data structure whose fields are initialized with the given values. </summary>
                /// <param name="...values"> A list of values with which the structure should be initialized. </param>
                /// <remarks> Field values must be provided in the same order as the structure field type list. </remarks>
                Structure(T ... values)
                {
                    Array<byte*, Count> v = { Cast<byte*>(values)... };
                    for (uint a = 0; a < Count; a++)
                        std::copy( v(a), v(a) + Types::Sizes[a], &_data(Offsets(a)) );
                }



                /** UTILITIES **/
                template<uint N> 
                constexpr static auto Attribute()
                {
                    return Utilities::Attribute<Structure, Types::Get<N>>
                    (
                        &Structure::Get<N>, 
                        &Structure::Set<N>
                    );
                }
                template<typename U> auto Append(U value)
                {
                    Structure<T..., U> output;
                    std::memcpy(&output, this, Size);
                    output.Set<Count>(value);
                    return output;
                }
                /// <summary> Gets the value of a particular structure field. </summary>
                /// <returns> The value at the inputted field index. </returns>
                /// <typeparam name="N"> The numeric index of the desired field. </typeparam>
                template<uint N> auto Get()                 const
                {
                    return *Cast< const Types::Get<N>* >(_data(Offsets(N)));
                }
                template<typename U> U Get(uint index)      const
                {
                    if (Types::IsEqual<U>(index))
                        return *Cast<const U*>(_data(Offsets(index)));
                    else
                        throw std::exception("Invalid return type!");
                }
                template<uint N> auto Property()
                {
                    return Utilities::Property<Structure, Types::Get<N>>
                    (
                        this,
                        &Structure::Get<N>,
                        &Structure::Set<N>
                    );
                }
                /// <summary> Sets the value of a particular structure field. </summary>
                /// <typeparam name="N"> The numeric index of the desired field. </typeparam>
                /// <param name="value"> The value to be copied into the structure. </param>
                template<uint N> Structure& Set(Types::Get<N> value)
                { 
                    byte* v1 = Cast<byte*>(value);
                    std::copy(v1, v1 + Types::Sizes[N], &_data(Offsets(N)));
                    return *this;
                }

        };

    }
}
