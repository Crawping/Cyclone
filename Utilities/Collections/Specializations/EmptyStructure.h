/* CHANGELOG
 * Written by Josh Grooms on 20170627
 */

#pragma once



namespace Cyclone
{
    namespace Utilities
    {
        template<> struct Structure<>
        {
            /// <summary> A list of the types that are stored in the structure. </summary>
            //using Types = Meta::List<>;

            /// <summary> The number of data fields in the structure. </summary>
            constexpr const static uint Count       = 0;
            /// <summary> The byte offsets of the data fields in the structure. </summary>
            constexpr const static uint Offsets     = 0;
            /// <summary> The total size of one structure instance in bytes. </summary>
            constexpr const static uint Size        = 0;

            public:

                /** CONSTRUCTORS **/
                /// <summary> Creates a new data structure instance whose fields are uninitialized. </summary>
                Structure() { }



                /** UTILITIES **/
                template<uint N> 
                constexpr static auto Attribute()
                {
                    return Utilities::Attribute<Structure>();
                }
                template<typename U>
                constexpr static auto GetAttribute(uint index)
                {
                    return Attribute<0>();
                }
                template<typename U> auto Append(U value)
                {
                    return Structure<U>(value);
                }
                /// <summary> Gets the value of a particular structure field. </summary>
                /// <returns> The value at the inputted field index. </returns>
                /// <typeparam name="N"> The numeric index of the desired field. </typeparam>
                template<uint N> auto Get()                 const
                {
                    return nullptr;
                }
                template<typename U> U Get(uint index)      const
                {
                    return nullptr;
                }
                template<uint N> auto Property()
                {
                    return Attribute<0>().Bind(this);
                }
                template<typename U> auto Property(uint index)
                {
                    return Attribute<0>().Bind(this);
                }
                /// <summary> Sets the value of a particular structure field. </summary>
                /// <typeparam name="N"> The numeric index of the desired field. </typeparam>
                /// <param name="value"> The value to be copied into the structure. </param>
                template<uint N> Structure& Set(void* value)
                { 
                    return *this;
                }
        };
    }
}
