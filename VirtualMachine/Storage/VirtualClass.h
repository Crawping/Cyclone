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
                int ID()                            const { return _type.TargetType(); }
                uint InstanceCount()                const { return _instances.Count(); }
                uint MethodCount()                  const { return _methods.Count(); }
                uint PropertyCount()                const { return _properties.Count(); }
                const VirtualReference& Type()      const { return _type; }



                /** CONSTRUCTOR **/
                VirtualClass(uint id = 0) :
                    _type(VariableTypes::Type, id)
                {

                }



                /** UTILITIES **/
                VMAPI const Vector<Instruction>& Call(uint method)                          const;
                VMAPI void Delete(uint instance);
                VMAPI VirtualVariable& Get(uint object, uint property);
                VMAPI void Insert(const VirtualFunction& function);
                VMAPI void Insert(const VirtualProperty& property);
                VMAPI bool IsMethod(uint id)                                                const;
                VMAPI bool IsOfType(const VirtualVariable& object)                          const;
                VMAPI void Set(uint object, uint property, const VirtualVariable& value);
                VMAPI const VirtualReference& TypeOf(uint property)                         const;
            private:

                int                         _id;
                VirtualReference            _type;
                SortedSet<uint>             _instances;
                BST<uint, VirtualFunction>  _methods;
                BST<uint, VirtualProperty>  _properties;

        };
    }
}
