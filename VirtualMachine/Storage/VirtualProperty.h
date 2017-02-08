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
                const VirtualVariable& Type()       const { return _type; }



                /** CONSTRUCTOR **/
                VMAPI VirtualProperty();
                VMAPI VirtualProperty(uint id, const VirtualVariable& type);



                /** UTILITIES **/
                VMAPI void Delete(uint instance);
                VMAPI VirtualVariable& Get(uint instance);
                VMAPI void Set(uint instance, const VirtualVariable& value);

            private:

                int                         _id;
                VirtualVariable             _type;
                BST<uint, VirtualVariable>  _instances;
        };

        class VirtualFunction
        {
            public:

                /** PROPERTIES **/
                int ID()                            const { return _id; }
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

    }
}
