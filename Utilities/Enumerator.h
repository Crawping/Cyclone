/* CHANGELOG
 * Written by Josh Grooms on 20151101
 */

/* TODO:
 *  - Find a more elegant way to deal with this issue in C++
 *  - Update documentation, particularly for the 'Flag' structure
 */

#pragma once
#include "TypeDefinitions.h"
#include "UtilitiesAPI.h"


namespace Cyclone
{
    namespace Utilities
    {

        /// <summary> The base structure for all of the custom-written enumerations found within this project. </summary>
        /// <remarks>
        ///     While working on this and related projects, I have at several points wished that C++ possessed native support for scoped
        ///     but weakly-typed enumerators. Such entities would be extremely helpful when working with code that expects the old plain
        ///     C 'enums' because it would then be possible to create libraries of new, well-scoped enumerators that could be freely
        ///     substituted for old values without manually writing conversion steps (i.e. 'static_cast<int>(enumClassType)' and the like).
        ///     Additionally, creating new libraries would provide an opportunity to write in-source documentation (which is where it
        ///     belongs in an API meant for use by programmers), cleanup messy conventions, and de-clutter the global (or other) namespace.
        ///     
        ///     However, C++ forces us to choose between one or the other enumerator type: either scoped and strongly typed enumerations
        ///     (i.e. 'enum classes'), or unscoped and weakly typed ones (i.e. plain C 'enums'). Scoped enumerators are great at not
        ///     cluttering namespaces and at being self-describing, but are difficult to work with when faced with code that expects plain
        ///     enumerators. On the other hand, plain enumerators are much more flexibly castable but require some awkward coding in order
        ///     to keep them scoped out of namespaces while retaining sensible semantics.
        ///     
        ///     I created the structure definition below as part of a simple system to work around that problem. Its purpose is to serve
        ///     as a base from which user-defined enumerators can be derived and freely converted to plain 'enum' equivalents. To do this,
        ///     it converts and stores an enumerator's value as a signed integer instead of the user-defined enumeration type. Any
        ///     enumerator instances then implicitly convert to pure integer values whenever used in functions expecting old plain 'enums'.
        ///     
        ///     Unfortunately, one consequence of this approach is that these enumerators do not easily convert to their newer 'enum class'
        ///     counterparts and therefore should not be used with code that is expecting arguments or parameters of those types. Another
        ///     consequence is that, for now anyway, all enumerations derived from 'Enumerator' resolve only to integers; I've toyed with
        ///     the idea of making this base structure a generic template, but for now I'm leaving things as they are (which currently
        ///     meets my needs nicely).
        /// </remarks>
        struct Enumerator
        {
            protected:

                /// <summary> The equivalent integer value of this enumerator. </summary>
                int Value;

				/// <summary> Constructs a basic integer storage structure for a derived enumerator value. </summary>
                constexpr Enumerator(int value = 0) : Value(value) { }

                constexpr Enumerator(const Enumerator& other) : Value(other.Value) { }

            public:

                /// <summary> Implicitly converted an Enumerator value into an integer. </summary>
		        constexpr operator int() const { return Value; }
        };
                
        /// <summary> The base structure for all custom-written flag enumerations found within this project. </summary>
        /// <remarks>
        ///     This class is nearly identical to the 'Enumerator' class above in both form and function. The most important difference between
        ///     them is that flags typically support bitwise operations that allow multiple values to be combined together in a single, highly
        ///     compact representation. To that end, this class exposes its 'Value' field to derived types and is deliberately more cautious
        ///     around casting to and from integer primitives.
        /// </remarks>
		template<typename T>
        struct Flag : public Enumerator
        {
			public:

                T operator &(T other)               { T copy(other); copy.Value &= Value; return copy; }
                T operator |(T other)               { T copy(other); copy.Value |= Value; return copy; }

                void operator &=(T other)           { Value &= other.Value; }
				void operator |=(T other)           { Value |= other.Value; }


            protected:
                /// <summary> Constructs a basic integer storage structure for a derived enumerator flag value. </summary>
		        constexpr Flag(int value) : Enumerator(value) { }
                
        };
    }
}