/* CHANGELOG
 * Written by Josh Grooms on 20170128
 */

#pragma once
#include "Collections/Set.h"
#include "Storage/VirtualProperty.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace VM
    {
        class VirtualClass
        {
            public:

                template<typename T> using SortedSet = Utilities::Set<T>;



                /** PROPERTIES **/
                int ID()                            const { return _id; }
                uint InstanceCount()                const { return _instances.Count(); }
                uint MethodCount()                  const { return _methods.Count(); }
                uint PropertyCount()                const { return _properties.Count(); }
                VariableTypes Type()                const { return VariableTypes::Type; }



                /** CONSTRUCTOR **/
                VirtualClass(uint id = 0) : _id(id) { }



                /** UTILITIES **/
                VMAPI void Delete(uint instance);
                VMAPI VirtualVariable& Get(uint object, uint property);
                VMAPI void Insert(const VirtualFunction& function);
                VMAPI void Insert(const VirtualProperty& property);
                VMAPI bool IsMethod(uint id)                                        const;
                VMAPI bool IsOfType(const VirtualVariable& object)                  const;

                VMAPI void Set(uint object, uint property, const VirtualVariable& value);

            private:

                int                         _id;
                //BST<uint, VirtualVariable>  _instances;
                SortedSet<uint>             _instances;
                BST<uint, VirtualFunction>  _methods;
                BST<uint, VirtualProperty>  _properties;

        };
    }
}
