/* CHANGELOG
 * Written by Josh Grooms on 20170204
 */

#pragma once
#include "Collections/ListVector.h"
#include "Virtual/Variable.h"



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
                    VMAPI Variable& Get(uint index);
                    VMAPI void Set(uint index, const Variable& value);

                private:

                    ListVector<Variable>    _data;
                    uint                    _id;
                
            };

        }
    }
}
