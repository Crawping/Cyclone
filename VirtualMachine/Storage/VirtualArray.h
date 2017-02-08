/* CHANGELOG
 * Written by Josh Grooms on 20170204
 */

#pragma once
#include "Collections/ListVector.h"
#include "Storage/VirtualVariable.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace VM
    {
        class VirtualArray
        {

            public:
                
                uint Count()            const { return _data.Count(); }

                VMAPI VirtualArray(uint id = 0);
                
                VMAPI VirtualArray Calculate(Instructions operation, const VirtualArray& other);
                VMAPI VirtualVariable& Get(uint index);
                VMAPI void Set(uint index, const VirtualVariable& value);

            private:

                ListVector<VirtualVariable> _data;
                uint                        _id;
                
        };
    }
}
