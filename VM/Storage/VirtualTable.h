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

                /** PROPERTIES **/
                uint ClassCount()       const { return Classes.Count(); }
                uint FunctionCount()    const { return Functions.Count(); }
                uint VariableCount()    const { return Variables.Count() - 1; }



                /** CONSTRUCTOR **/
                VMAPI VirtualTable();



                /** UTILITIES **/
                VMAPI void Delete(uint id);
                VMAPI void Insert(const VirtualClass& type);
                VMAPI void Insert(const VirtualFunction& function);
                VMAPI uint Insert(const string& string);
                VMAPI uint Insert(const string& name, const Literal& value);

                VMAPI Literal Get(uint id)  const;
                VMAPI Literal Get(uint type, uint property, uint instance) const;

                VMAPI void Set(uint id, const Literal& value);
                VMAPI void Set(uint type, uint property, uint instance, const Literal& value);
                
                VMAPI string FindName(uint id)          const;
                VMAPI uint FindID(const string& name)   const;

            private:

                BST<uint, VirtualClass>     Classes;
                BST<uint, VirtualFunction>  Functions;
                BST<uint, string>           Strings;
                BST<uint, Literal>          Variables;

        };

    }
}
