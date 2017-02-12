/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "VMAPI.h"
#include "Collections/Registry.h"
#include "Storage/VirtualVariable.h"
#include "Storage/VirtualReference.h"



namespace Cyclone
{
    namespace VM
    {
        class VirtualProperty
        {
            public:

                /** PROPERTIES **/
                int ID()                            const { return _id; }
                const VirtualReference& Type()      const { return _type; }



                /** CONSTRUCTOR **/
                VMAPI VirtualProperty();
                VMAPI VirtualProperty(uint id, const VirtualReference& type);



                /** UTILITIES **/
                VMAPI void Delete(uint instance);
                VMAPI VirtualVariable& Get(uint instance);
                VMAPI void Set(uint instance, const VirtualVariable& value);

            private:

                int                         _id;
                VirtualReference            _type;
                BST<uint, VirtualVariable>  _instances;
        };
    }
}
