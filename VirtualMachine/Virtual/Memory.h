/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "Collections/BST.h"
#include "Primitives/Number.h"
#include "Storage/Address.h"
#include "Storage/StringLibrary.h"
#include "Virtual/Array.h"
#include "Virtual/Class.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {

            class Memory
            {

                public:

                    /** PROPERTIES **/
                    /// <summary> Gets the number of classes that have been defined in virtual memory. </summary>
                    uint ClassCount()       const { return Classes.Count() - 1; }
                    /// <summary> Gets the number of functions that have been defined in virtual memory. </summary>
                    uint FunctionCount()    const { return Functions.Count() - 1; }
                    /// <summary> Gets the number of variables that have been defined in virtual memory. </summary>
                    uint ReferenceCount()   const { return References.Count() - 1; }



                    /** CONSTRUCTOR **/
                    /// <summary> Constructs an empty virtual memory pool that can be used with virtual machines. </summary>
                    VMAPI Memory();



                    /** UTILITIES **/
                    //VMAPI Variable& Access(Reference location);
                    template<typename T = Variable>
                    VMAPI T& Access(Reference location);
                    //VMAPI Function& Call(Reference location);
                    //VMAPI void Delete(Reference location);
                    //VMAPI Array& Index(Reference location);
                    //VMAPI Class& TypeOf(Reference location);

                    //VMAPI const Vector<Instruction>& Call(const Variable& function)         const;
                    //VMAPI const Vector<Instruction>& CallFunction(uint id)                  const;
                    //VMAPI const Vector<Instruction>& CallMethod(uint type, uint method)     const;

                    //VMAPI void CopyArray(uint source, uint destination);
                    //VMAPI void CopyObject(uint type, uint source, uint destination);

                    //VMAPI void Delete(const Variable& reference);
                    //VMAPI void DeleteArray(uint id);
                    //VMAPI void DeleteObject(uint type, uint id);
                    //VMAPI void DeleteVariable(uint id);

                    //VMAPI const string& Find(uint id)                                   const;
                    //VMAPI uint Find(const string& name)                                 const;

                    //VMAPI Variable& Get(const Variable& reference, const Variable& property);
                    //VMAPI Variable& GetArray(uint id, uint index);
                    //VMAPI Variable& GetObject(uint type, uint property, uint id);
                    //VMAPI Variable& GetVariable(uint id);

                    //VMAPI void Insert(const Class& type);
                    //VMAPI void Insert(const Function& function);
                    //VMAPI void Insert(uint type, const Property& property);
                    //VMAPI uint Insert(const string& string);
                    //VMAPI uint Insert(const string& name, const Variable& value);

                    //VMAPI void Set(const Variable& reference, const Variable& property, const Variable& value);
                    //VMAPI void SetArray(uint id, uint index, const Variable& value);
                    //VMAPI void SetObject(uint type, uint property, uint id, const Variable& value);
                    //VMAPI void SetVariable(uint id, const Variable& value);


                private:

                    BST<uint, Array>        Arrays;
                    BST<uint, Class>        Classes;
                    BST<uint, Function>     Functions;
                    BST<uint, Number>       Numbers;
                    BST<uint, Reference>    References;
                    BST<uint, string>       Strings;

            };

        }
    }
}
