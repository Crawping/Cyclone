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
                //VMAPI void Insert(const Literal& value);
                //VMAPI Literal Insert(const string& name);
                VMAPI Literal Insert(const VirtualClass& type);
                VMAPI Literal Insert(const VirtualFunction& function);
                VMAPI Literal Insert(const string& string);

                //VMAPI Literal Get(const Literal& object);
                VMAPI Literal Get(const Literal& object, const Literal& property);

                VMAPI Vector<Instructions>& Call(const Literal& function);
                VMAPI Vector<Instructions>& Call(const Literal& object, const Literal& method);
                
                VMAPI string FindName(uint id)          const;
                VMAPI int FindID(const string& name)    const;

            private:

                BST<uint, VirtualClass>     Classes;
                BST<uint, VirtualFunction>  Functions;
                BST<uint, string>           Strings;

        };

    }
}
