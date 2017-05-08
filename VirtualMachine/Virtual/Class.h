/* CHANGELOG
 * Written by Josh Grooms on 20170128
 */

#pragma once
#include "Collections/Set.h"
#include "Storage/Reference.h"
#include "Virtual/Function.h"
#include "Virtual/Property.h"



namespace Cyclone
{
    using namespace Utilities;
    namespace Virtual
    {

        class Class
        {
            public:

                template<typename T> using SortedSet = Utilities::Set<T>;



                /** PROPERTIES **/
                /// <summary> Gets the number of existing class instances. </summary>
                uint InstanceCount()        const { return _instances.Count(); }
                /// <summary> Gets the number of methods associated with the class.  </summary>
                uint MethodCount()          const { return _methods.Count(); }
                /// <summary> Gets the number of properties associated with the class. </summary>
                uint PropertyCount()        const { return _properties.Count(); }



                /** CONSTRUCTOR **/
                Class() { }
                Class(Class&& other)        = default;
                Class(const Class& other)   = default;
                        


                /** UTILITIES **/
                VMAPI Reference& Access(Reference location);



                /** OPERATORS **/
                VMAPI Class& operator =(Class&& other) noexcept;
                VMAPI Class& operator =(const Class& other);

            private:

                SortedSet<uint>         _instances;
                BST<uint, Function>     _methods;
                BST<uint, Property>     _properties;

        };

    }
}
