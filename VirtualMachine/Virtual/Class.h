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
                Class(uint id = 0);
                Class(Class&& other)        = default;
                Class(const Class& other)   = default;
                        


                /** UTILITIES **/
                VMAPI Reference& Access(Reference location);
                //VMAPI const Vector<Instruction>& Call(Reference location) const;

                //VMAPI void Delete(uint instance);
                //VMAPI Variable& Get(uint object, uint property);
                //VMAPI void Insert(Function&& function);
                //VMAPI void Insert(Property&& property);
                //VMAPI bool IsMethod(uint id)                                                const;
                //VMAPI bool IsOfType(const Variable& object)                                 const;
                //VMAPI void Set(uint object, uint property, const Variable& value);



                /** OPERATORS **/
                Class& operator =(Class&& other)       noexcept
                {
                    _id = other._id;
                    _instances = std::move(other._instances);
                    _methods = std::move(other._methods);
                    _properties = std::move(other._properties);
                    return *this;
                }
                Class& operator =(const Class& other)
                {

                    return *this;
                }

            private:

                SortedSet<uint>         _instances;
                BST<uint, Function>     _methods;
                BST<uint, Property>     _properties;

        };

    }
}
