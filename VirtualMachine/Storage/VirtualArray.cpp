#include "Storage/VirtualArray.h"



namespace Cyclone
{
    namespace VM
    {
        VirtualArray::VirtualArray(uint id) : _id(id) { }

        VirtualArray VirtualArray::Calculate(Instructions operation, const VirtualArray& other)
        {
            return VirtualArray();
        }
        VirtualVariable& VirtualArray::Get(uint index)
        {
            return _data(index);
        }
        void VirtualArray::Set(uint index, const VirtualVariable& value)
        {
            if (index >= Count()) { return; }
            _data(index) = value;
        }
    }
}