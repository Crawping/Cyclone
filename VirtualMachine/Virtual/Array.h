/* CHANGELOG
 * Written by Josh Grooms on 20170204
 */

#pragma once
#include "Collections/ListVector.h"
#include "Execution/Instructions.h"


namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace VM
    {
        namespace Virtual
        {

            class Array
            {

                public:
                
                    uint Count()            const { return _data.Count(); }

                    VMAPI Array(uint id = 0);
                
                    VMAPI Array Calculate(Instructions operation, const Array& other);
                    VMAPI Reference& Get(uint index);
                    VMAPI void Set(uint index, const Reference& value);

                private:

                    ListVector<Reference>   _data;
                    uint                    _id;
                
            };

        }
    }
}
