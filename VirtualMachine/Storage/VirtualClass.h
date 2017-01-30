/* CHANGELOG
 * Written by Josh Grooms on 20170128
 */

#pragma once
#include "Storage/VirtualProperty.h"



namespace Cyclone
{
    namespace VM
    {
        class VirtualClass
        {
            public:

                /** PROPERTIES **/
                int ID()                            const { return _id; }
                LiteralTypes Type()                 const { return LiteralTypes::Type; }



                /** CONSTRUCTOR **/
                VirtualClass(uint id = 0) : _id(id) { }



                /** UTILITIES **/
                VMAPI Literal& Access(uint instance, uint property);
                VMAPI const Literal& Access(uint instance, uint property)   const;
                VMAPI Literal Get(uint object, uint property)               const;
                VMAPI void Insert(const VirtualFunction& function);
                VMAPI void Insert(const VirtualProperty& property);
                VMAPI bool IsMethod(uint id)                                const;
                VMAPI bool IsOfType(const Literal& object)                  const;

                VMAPI void Set(uint object, uint property, const Literal& value);

            private:

                int                         _id;
                BST<uint, Literal>          _instances;
                BST<uint, VirtualFunction>  _methods;
                BST<uint, VirtualProperty>  _properties;

        };
    }
}
