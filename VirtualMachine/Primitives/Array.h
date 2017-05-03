/* CHANGELOG
 * Written by Josh Grooms on 20170204
 */

#pragma once
#include "Collections/ListVector.h"
#include "Execution/Instructions.h"
#include "Primitives/Number.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace Virtual
    {

        class Array
        {

            public:
                
                /** PROPERTIES **/
                /// <summary> Gets the number of elements that are stored in the array. </summary>
                uint Count()            const { return _data.Count(); }
                /// <summary> Gets the type of elements that are stored in the array. </summary>
                ReferenceTypes Type()   const { return _type; }



                /** CONSTRUCTOR **/
                VMAPI Array(ReferenceTypes type = 0);



                /** UTILITIES **/
                VMAPI Number& Access(Reference location);
                //template<typename T>
                //VMAPI T& Access(Reference location);
                //VMAPI Array(uint id = 0);
                
                //VMAPI Array Calculate(Instructions operation, const Array& other);
                //VMAPI Reference& Get(uint index);
                //VMAPI void Set(uint index, const Reference& value);

            private:

                ListVector<Number>		_data;
                ReferenceTypes          _type;
                
        };

    }
}
