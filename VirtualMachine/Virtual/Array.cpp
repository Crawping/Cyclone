#include "Virtual/Array.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {

            Array::Array(uint id) : _id(id) { }

            Array Array::Calculate(Instructions operation, const Array& other)
            {
                return Array();
            }
            Variable& Array::Get(uint index)
            {
                return _data(index);
            }
            void Array::Set(uint index, const Variable& value)
            {
                if (index >= Count()) { return; }
                _data(index) = value;
            }

        }
    }
}