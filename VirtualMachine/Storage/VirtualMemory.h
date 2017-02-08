/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "Collections/BST.h"
#include "Storage/StringLibrary.h"
#include "Storage/VirtualArray.h"
#include "Storage/VirtualClass.h"



namespace Cyclone
{
    namespace VM
    {

        class VirtualMemory
        {

            public:

                /** PROPERTIES **/
                /// <summary> Gets the number of classes that have been defined in virtual memory. </summary>
                uint ClassCount()       const { return Classes.Count() - 1; }
                /// <summary> Gets the number of functions that have been defined in virtual memory. </summary>
                uint FunctionCount()    const { return Functions.Count() - 1; }
                /// <summary> Gets the number of variables that have been defined in virtual memory. </summary>
                uint VariableCount()    const { return Variables.Count() - 1; }



                /** CONSTRUCTOR **/
                /// <summary> Constructs an empty virtual memory pool that can be used with virtual machines. </summary>
                VMAPI VirtualMemory();



                /** UTILITIES **/
                VMAPI void CopyArray(uint source, uint destination);
                VMAPI void CopyObject(uint type, uint source, uint destination);
                VMAPI uint Define(VariableTypes type, const string& name);
                
                VMAPI void Delete(const VirtualVariable& reference);
                VMAPI void DeleteArray(uint id);
                VMAPI void DeleteObject(uint type, uint id);
                VMAPI void DeleteVariable(uint id);
                
                VMAPI const string& Find(uint id)                                   const;
                VMAPI uint Find(const string& name)                                 const;

                VMAPI VirtualVariable& Get(const VirtualVariable& reference, const VirtualVariable& property);
                VMAPI VirtualVariable& GetArray(uint id, uint index);
                VMAPI VirtualVariable& GetObject(uint type, uint property, uint id);
                VMAPI VirtualVariable& GetVariable(uint id);

                VMAPI void Insert(const VirtualClass& type);
                VMAPI void Insert(const VirtualFunction& function);
                VMAPI void Insert(uint type, const VirtualProperty& property);
                VMAPI uint Insert(const string& string);
                VMAPI uint Insert(const string& name, const VirtualVariable& value);

                VMAPI void Set(const VirtualVariable& reference, const VirtualVariable& property, const VirtualVariable& value);
                VMAPI void SetArray(uint id, uint index, const VirtualVariable& value);
                VMAPI void SetObject(uint type, uint property, uint id, const VirtualVariable& value);
                VMAPI void SetVariable(uint id, const VirtualVariable& value);


            private:

                BST<uint, VirtualArray>     Arrays;
                BST<uint, VirtualClass>     Classes;
                BST<uint, VirtualFunction>  Functions;
                StringLibrary               Strings;
                BST<uint, VirtualVariable>  Variables;

        };

    }
}
