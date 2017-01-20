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
                //const string& Name()                const { return _name; }
                //LiteralTypes Type()                 const { return _value.Type; }



                /** CONSTRUCTOR **/
                VMAPI VirtualProperty();

            private:

                uint                _id;
                Registry<Literal>   _instances;
                //string              _name;
        };

        class VirtualFunction
        {
            public:

                uint ID()                           const { return _id; }
                const Vector<Instructions>& Logic() const { return _logic; }
                //const string& Name()                const { return _name; }
                LiteralTypes Type()                 const { return LiteralTypes::Function; }

            private:

                uint    _id;
                //string  _name;

                Vector<Instructions> _logic;
        };

        class VirtualClass
        {
            public:
                
                /** PROPERTIES **/
                uint ID()                           const { return _id; }
                //const string& Name()                const { return _name; }
                LiteralTypes Type()                 const { return LiteralTypes::Type; }



                /** UTILITIES **/
                VMAPI Literal Get(const Literal& object, const Literal& property);
                VMAPI void Set(const Literal& object, const Literal& property, const Literal& value);

            private:

                uint                        _id;
                Registry<Literal>           _instances;
                BST<uint, VirtualFunction>  _methods;
                //string                      _name;
                BST<uint, VirtualProperty>  _properties;

        };

    }
}
