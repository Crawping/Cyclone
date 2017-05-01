/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "Collections/BST.h"
#include "Primitives/Number.h"
#include "Storage/Reference.h"
#include "Storage/StringLibrary.h"
#include "Virtual/Array.h"
#include "Virtual/Class.h"
#include "Virtual/Function.h"



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
                    uint ArrayCount()       const { return Arrays.Count() - 1; }
                    /// <summary> Gets the number of classes that have been defined in virtual memory. </summary>
                    uint ClassCount()       const { return Classes.Count() - 1; }
                    /// <summary> Gets the number of functions that have been defined in virtual memory. </summary>
                    uint FunctionCount()    const { return Functions.Count() - 1; }

                    uint NumberCount()      const { return Numbers.Count() - 1; }
                    /// <summary> Gets the number of variables that have been defined in virtual memory. </summary>
                    uint ReferenceCount()   const { return References.Count() - 1; }

                    uint StringCount()      const { return Strings.Count() - 1; }



                    /** CONSTRUCTOR **/
                    /// <summary> Constructs an empty virtual memory pool that can be used with virtual machines. </summary>
                    VMAPI Memory();


                    
                    /** UTILITIES **/
                    //VMAPI Variable& Access(Reference location);
                    template<typename T = Variable>
                    VMAPI T& Access(Reference location);

                    template<typename T>
                    VMAPI void Insert(Reference location, const T& value);

                    VMAPI void Remove(Reference location);

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



            /** TEMPLATE SPECIALIZATIONS **/
            template<> VMAPI Array& Memory::Access<Array>(Reference location);
            template<> VMAPI Class& Memory::Access<Class>(Reference location);
            template<> VMAPI Function& Memory::Access<Function>(Reference location);
            template<> VMAPI Number& Memory::Access<Number>(Reference location);
            template<> VMAPI Reference& Memory::Access<Reference>(Reference location);
            template<> VMAPI string& Memory::Access<string>(Reference location);

            template<> VMAPI void Memory::Insert<Array>(Reference location, const Array& value);
            template<> VMAPI void Memory::Insert<Class>(Reference location, const Class& value);
            template<> VMAPI void Memory::Insert<Function>(Reference location, const Function& value);
            template<> VMAPI void Memory::Insert<Number>(Reference location, const Number& value);
            template<> VMAPI void Memory::Insert<Reference>(Reference location, const Reference& value);
            template<> VMAPI void Memory::Insert<string>(Reference location, const string& value);

        }
    }
}
