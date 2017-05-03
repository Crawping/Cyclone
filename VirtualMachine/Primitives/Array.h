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
    namespace VM
    {
        namespace Virtual
        {

            class Array
            {

                public:
                
                    /** PROPERTIES **/
                    uint Count()            const { return _data.Count(); }
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
}
