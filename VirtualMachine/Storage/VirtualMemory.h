/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "Collections/BST.h"
#include "Storage/StringLibrary.h"
#include "Storage/VirtualProperty.h"



namespace Cyclone
{
    namespace VM
    {

        class VirtualMemory
        {
            public:

                /** PROPERTIES **/
                uint ClassCount()       const { return Classes.Count(); }
                uint FunctionCount()    const { return Functions.Count(); }
                uint VariableCount()    const { return Variables.Count() - 1; }



                /** CONSTRUCTOR **/
                VMAPI VirtualMemory();



                /** UTILITIES **/
                VMAPI Literal& Access(uint id);
                VMAPI Literal& Access(uint type, uint property, uint instance);

                VMAPI void Delete(uint id);
                VMAPI const string& Find(uint id)                           const;
                VMAPI uint Find(const string& name)                         const;
                VMAPI Literal Get(uint id)                                  const;
                VMAPI Literal Get(uint type, uint property, uint instance)  const;

                VMAPI void Insert(const VirtualClass& type);
                VMAPI void Insert(const VirtualFunction& function);
                VMAPI uint Insert(const string& string);
                VMAPI uint Insert(const string& name, const Literal& value);

                VMAPI void Set(uint id, const Literal& value);
                VMAPI void Set(uint type, uint property, uint instance, const Literal& value);
                
            private:

                BST<uint, VirtualClass>     Classes;
                BST<uint, VirtualFunction>  Functions;
                StringLibrary               Strings;
                BST<uint, Literal>          Variables;

        };

    }
}
