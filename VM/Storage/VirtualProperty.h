/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "VMAPI.h"
#include "Collections/Registry.h"
#include "Storage/Literal.h"



namespace Cyclone
{
    namespace VM
    {

        class VirtualProperty
        {
            public:

                /** PROPERTIES **/
                uint ID()                           const { return _id; }



                /** CONSTRUCTOR **/
                VMAPI VirtualProperty(uint id = 0);



                /** UTILITIES **/
                VMAPI Literal Get(uint instance)    const;
                VMAPI void Set(uint instance, const Literal& value);

            private:

                uint                _id;
                BST<uint, Literal>  _instances;
        };

        class VirtualFunction
        {
            public:

                /** PROPERTIES **/
                uint ID()                           const { return _id; }
                uint InputCount()                   const { return _inputCount; }
                const Vector<Instructions>& Logic() const { return _logic; }
                uint OutputCount()                  const { return _outputCount; }

                VirtualFunction(uint id = 0) : _id(id) { }

            private:

                uint                    _id;
                uint                    _inputCount;
                Vector<Instructions>    _logic;
                uint                    _outputCount;
        };

        class VirtualClass
        {
            public:
                
                /** PROPERTIES **/
                uint ID()                           const { return _id; }
                LiteralTypes Type()                 const { return LiteralTypes::Type; }

                /** CONSTRUCTOR **/
                VirtualClass(uint id = 0) : _id(id) { }

                /** UTILITIES **/
                VMAPI void Insert(const VirtualFunction& function);
                VMAPI void Insert(const VirtualProperty& property);
                VMAPI Literal Get(uint object, uint property)   const;
                VMAPI bool IsOfType(const Literal& object)      const;
                bool IsMethod(uint id)                          const { return _methods.Contains(id); }

                VMAPI void Set(uint object, uint property, const Literal& value);

            private:

                uint                        _id;
                BST<uint, Literal>          _instances;
                BST<uint, VirtualFunction>  _methods;
                BST<uint, VirtualProperty>  _properties;

        };

    }
}
