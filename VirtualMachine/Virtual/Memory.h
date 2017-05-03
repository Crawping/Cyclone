/* CHANGELOG
 * Written by Josh Grooms on 20170117
 */

#pragma once
#include "Collections/BST.h"
#include "Collections/String.h"
#include "Primitives/Array.h"
#include "Primitives/Number.h"
#include "Storage/Reference.h"
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
					/// <summary> Gets the number of arrays that have been defined in virtual memory. </summary>
                    uint ArrayCount()       const { return Arrays.Count() - 1; }
                    /// <summary> Gets the number of classes that have been defined in virtual memory. </summary>
                    uint ClassCount()       const { return Classes.Count() - 1; }
                    /// <summary> Gets the number of functions that have been defined in virtual memory. </summary>
                    uint FunctionCount()    const { return Functions.Count() - 1; }
					/// <summary> Gets the number of numeric variables that have been defined in virtual memory. </summary>
                    uint NumberCount()      const { return Numbers.Count() - 1; }
                    /// <summary> Gets the number of variables that have been defined in virtual memory. </summary>
                    uint ReferenceCount()   const { return References.Count() - 1; }
					/// <summary> Gets the number of strings that have been defined in virtual memory. </summary>
                    uint StringCount()      const { return Strings.Count() - 1; }



                    /** CONSTRUCTOR **/
                    /// <summary> Constructs an empty virtual memory pool that can be used with virtual machines. </summary>
                    VMAPI Memory();


                    
                    /** UTILITIES **/
					/// <summary> Gets a mutable reference to a specific element stored in virtual memory. </summary>
					/// <returns> A reference to the desired element, or a null reference if no such element exists. </returns>
					/// <typeparam name="T"> The type of the element being accessed. </typeparam>
					/// <param name="location"> A data structure that defines the location of the desired element in memory. </param>
                    template<typename T = Variable>
                    VMAPI T& Access(Reference location);
					/// <summary> Inserts a new data element into the virtual memory. </summary>
                    template<typename T>
                    VMAPI void Insert(Reference location, const T& value);
					/// <summary> erases a specific data element from virtual memory. </summary>
                    VMAPI void Delete(Reference location);

                private:

                    BST<uint, Array>        Arrays;
                    BST<uint, Class>        Classes;
                    BST<uint, Function>     Functions;
                    BST<uint, Number>       Numbers;
                    BST<uint, Reference>    References;
                    BST<uint, String>       Strings;

            };



            /** TEMPLATE SPECIALIZATIONS **/
            template<> VMAPI Array& Memory::Access<Array>(Reference location);
            template<> VMAPI Class& Memory::Access<Class>(Reference location);
            template<> VMAPI Function& Memory::Access<Function>(Reference location);
            template<> VMAPI Number& Memory::Access<Number>(Reference location);
            template<> VMAPI Reference& Memory::Access<Reference>(Reference location);
            template<> VMAPI String& Memory::Access<String>(Reference location);

            template<> VMAPI void Memory::Insert<Array>(Reference location, const Array& value);
            template<> VMAPI void Memory::Insert<Class>(Reference location, const Class& value);
            template<> VMAPI void Memory::Insert<Function>(Reference location, const Function& value);
            template<> VMAPI void Memory::Insert<Number>(Reference location, const Number& value);
            template<> VMAPI void Memory::Insert<Reference>(Reference location, const Reference& value);
            template<> VMAPI void Memory::Insert<String>(Reference location, const String& value);

        }
    }
}
