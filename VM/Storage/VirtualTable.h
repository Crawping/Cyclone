/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "Collections/BST.h"
#include "Storage/VirtualProperty.h"



namespace Cyclone
{
    namespace VM
    {

        class VirtualTable
        {
            public:

                /** UTILITIES **/
                VMAPI void Insert(const Literal& value);

                VMAPI Literal Get(const Literal& type, const Literal& object);
                

                VMAPI Literal Call(const Literal& function);
                VMAPI Literal Call(const Literal& object, const Literal& method);

                

            private:

                BST<uint, VirtualClass>     Objects;
                BST<uint, VirtualFunction>  Functions;

        };

    }
}
