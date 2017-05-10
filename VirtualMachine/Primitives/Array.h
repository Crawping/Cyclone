/* CHANGELOG
 * Written by Josh Grooms on 20170204
 */

#pragma once
#include "Collections/ListVector.h"
#include "Execution/Instructions.h"
#include "Primitives/Number.h"



namespace Cyclone
{
    namespace Virtual
    {
        using namespace Utilities;

        class Array
        {

            public:
                
                /** PROPERTIES **/
                
                uint Capacity()         const { return _data.Capacity(); }
                /// <summary> Gets the number of elements that are stored in the array. </summary>
                uint Count()            const { return _data.Count(); }
                /// <summary> Gets whether the array has any stored elements. </summary>
                bool IsEmpty()          const { return Count() == 0; }
                /// <summary> Gets the type of elements that are stored in the array. </summary>
                ReferenceTypes Type()   const { return _type; }



                /** CONSTRUCTOR **/
                VMAPI Array(ReferenceTypes type = 0, uint capacity = 1);



                /** UTILITIES **/
                VMAPI Number& Access(Reference location);
                VMAPI void Insert(Reference location, Number value);
                VMAPI void Insert(Reference location, const ICollection<Number>& values);
                
                //VMAPI Array Calculate(Instructions operation, const Array& other);
                //VMAPI Reference& Get(uint index);
                //VMAPI void Set(uint index, const Reference& value);

            private:

                ArrayList<Number>		_data;
                ReferenceTypes          _type;
                
        };

    }
}
