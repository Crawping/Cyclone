/* CHANGELOG
 * Written by Josh Grooms on 20170212
 */

#pragma once
#include "Collections/Vector.h"
#include "Storage/VirtualReference.h"



namespace Cyclone
{
    namespace VM
    {
        class VirtualFunction
        {
            public:

                /** PROPERTIES **/
                int ID()                            const { return _id; }
                uint InputCount()                   const { return _inputCount; }
                const Vector<Instruction>& Logic()  const { return _logic; }
                uint OutputCount()                  const { return _outputCount; }



                /** CONSTRUCTOR **/
                VirtualFunction(uint id = 0) : _id(id) { }

            private:

                /** DATA **/
                uint                    _id;
                uint                    _inputCount;
                Vector<Instruction>     _logic;
                uint                    _outputCount;

        };
    }
}
