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
                //LiteralTypes Type()                 const { return _value.Type; }



                /** CONSTRUCTOR **/
                VMAPI VirtualProperty();



                /** UTILITIES **/
                VMAPI Literal Get(uint instance)    const;

            private:

                uint                _id;
                BST<uint, Literal>  _instances;
        };

        class VirtualFunction
        {
            public:

                /** PROPERTIES **/
                uint ID()                           const { return _id; }
                const Vector<Instructions>& Logic() const { return _logic; }
                LiteralTypes Type()                 const { return LiteralTypes::Function; }

            private:

                uint                    _id;
                Vector<Instructions>    _logic;
        };

        class VirtualClass
        {
            public:
                
                /** PROPERTIES **/
                uint ID()                           const { return _id; }
                LiteralTypes Type()                 const { return LiteralTypes::Type; }



                /** UTILITIES **/
                VMAPI Literal Get(uint object, uint property)   const;
                VMAPI bool IsOfType(const Literal& object)      const;
                VMAPI void Set(const Literal& object, const Literal& property, const Literal& value);

            private:

                uint                        _id;
                BST<uint, Literal>          _instances;
                BST<uint, VirtualFunction>  _methods;
                BST<uint, VirtualProperty>  _properties;

        };

    }
}
