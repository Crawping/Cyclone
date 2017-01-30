/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "Collections/BST.h"
#include "Storage/StringLibrary.h"
#include "Storage/VirtualClass.h"



namespace Cyclone
{
    namespace VM
    {

        class VirtualMemory
        {

            public:

                /** PROPERTIES **/
                uint ClassCount()       const { return Classes.Count() - 1; }
                uint FunctionCount()    const { return Functions.Count(); }
                uint VariableCount()    const { return Variables.Count() - 1; }



                /** CONSTRUCTOR **/
                VMAPI VirtualMemory();



                /** UTILITIES **/
                VMAPI VirtualVariable& Access(uint id);
                VMAPI VirtualVariable& Access(uint type, uint property, uint instance);

                VMAPI void Delete(uint id);
                VMAPI const string& Find(uint id)                                   const;
                VMAPI uint Find(const string& name)                                 const;
                VMAPI VirtualVariable Get(uint id)                                  const;
                VMAPI VirtualVariable Get(uint type, uint property, uint instance)  const;

                VMAPI void Insert(const VirtualClass& type);
                VMAPI void Insert(const VirtualFunction& function);
                VMAPI void Insert(uint type, const VirtualProperty& property);
                VMAPI uint Insert(const string& string);
                VMAPI uint Insert(const string& name, const VirtualVariable& value);

                VMAPI void Set(uint id, const VirtualVariable& value);
                VMAPI void Set(uint type, uint property, uint instance, const VirtualVariable& value);

            private:

                BST<uint, VirtualClass>     Classes;
                BST<uint, VirtualFunction>  Functions;
                StringLibrary               Strings;
                BST<uint, VirtualVariable>          Variables;

        };

    }
}
