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
                /// <summary> Gets the number of classes that have been defined in virtual memory. </summary>
                uint ClassCount()       const { return Classes.Count() - 1; }
                /// <summary> Gets the number of functions that have been defined in virtual memory. </summary>
                uint FunctionCount()    const { return Functions.Count(); }
                /// <summary> Gets the number of variables that have been defined in virtual memory. </summary>
                uint VariableCount()    const { return Variables.Count() - 1; }



                /** CONSTRUCTOR **/
                /// <summary> Constructs an empty virtual memory pool that can be used with virtual machines. </summary>
                VMAPI VirtualMemory();



                /** UTILITIES **/
                VMAPI VirtualVariable& Access(uint id);
                VMAPI VirtualVariable& Access(uint type, uint property, uint instance);

                /// <summary> Deletes a specific variable in the virtual memory pool. </summary>
                /// <param name="id"> The identifier of the variable to be deleted. </param>
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
                BST<uint, VirtualVariable>  Variables;

        };

    }
}
