/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "VMAPI.h"
#include "Collections/Registry.h"
#include "Storage/VirtualVariable.h"



namespace Cyclone
{
    namespace VM
    {

        class VirtualProperty
        {
            public:

                /** PROPERTIES **/
                int ID()                            const { return _id; }



                /** CONSTRUCTOR **/
                VMAPI VirtualProperty(uint id = 0);



                /** UTILITIES **/
                VMAPI VirtualVariable& Access(uint instance);
                VMAPI const VirtualVariable& Access(uint instance)              const;
                VMAPI VirtualVariable Get(uint instance)                        const;
                VMAPI void Set(uint instance, const VirtualVariable& value);

            private:

                int                 _id;
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
