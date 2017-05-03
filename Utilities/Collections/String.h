/* CHANGELOG
 * Written by Josh Grooms on 20170502
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone
{
	namespace Utilities
	{
		/// <summary> A class that represents a compile-time string of characters. </summary>
		struct String
		{
			public:

				/** PROPERTIES **/
				/// <summary> Gets the number of characters that are present in the string. </summary>
				constexpr uint Count()          const { return _count; }
				/// <summary> Gets whether the string is storing any characters. </summary>
				constexpr bool IsEmpty()        const { return Count() == 0; }
				/// <summary> Gets the native C++ array of characters that defines the string. </summary>
				constexpr const char* Value()   const { return _value; }



				/** CONSTRUCTOR **/
				/// <summmary> Constructs an empty new string. </summmary>
				constexpr String():
					_count(0),
					_value(0)
				{

				}
				/// <summary> Constructs a new string using a literal character array. </summary>
				template<uint N>
				constexpr String(const char(&value)[N]):
					_count(N - 1),
					_value(value)
				{

				}



				/** OPERATORS **/
				/// <summary> Implicitly converts a static string object into a standard C++ string. </summary>
				operator std::string()                      const { return Value(); }
				/// <summary> Gets the character at a specific position within the string. </summary>
				constexpr char operator ()(uint index)      const { return (index < Count()) ? Value()[index] : '\0'; }

				/// <summary> Determines whether two strings are equivalent to one another. </summary>
				bool operator ==(const std::string& other)  const { return string(*this) == other; }
				/// <summary> Determines whether two strings are not equivalent to one another. </summary>
				bool operator !=(const std::string& other)  const { return !(operator ==(other)); }

			private:

				uint        _count;
				const char* _value;

		};
	}
}
