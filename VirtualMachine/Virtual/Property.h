/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "VMAPI.h"
#include "Collections/Registry.h"
#include "Virtual/Function.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {

            class Property
            {
                public:

                    /** PROPERTIES **/
                    int ID()                            const { return _id; }



                    /** CONSTRUCTOR **/
                    VMAPI Property(uint id = 0);



                    /** UTILITIES **/

                    VMAPI void Delete(uint instance);
                    VMAPI Reference& Get(uint instance);
                    VMAPI void Set(uint instance, const Reference& value);

                    Property& operator =(const Property& other)
                    {
                        return *this;
                    }

                private:

                    uint                    _id;
                    BST<uint, Reference>     _instances;
            };

        }
    }
}
