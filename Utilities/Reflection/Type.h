/* CHANGELOG
 * Written by Josh Grooms on 20170419
 */

#pragma once
#include "Utilities.h"
#include "Collections/Set.h"
#include "Reflection/Metafunctions.h"



namespace Cyclone
{
    namespace Utilities
    {

        /** FORWARD DECLARATIONS **/
        class Field;
        using namespace Utilities;



        class Metaclass
        {
            public:
                
                /** PROPERTIES **/    
                uint ID()               const { return _id; }
                bool IsReference()      const { return _isReference; }
                bool IsPointer()        const { return _isPointer; }
                const string& Name()    const { return _name; }
                uint Size()             const { return _size; }



                /** STATIC CONSTRUCTOR **/
                template<typename T> static Metaclass Create()
                {
                    const auto& type = typeid(Dereference<T>::Class);

                    Metaclass m;
                    m._id           = type.hash_code();
                    m._isPointer    = Utilities::IsPointer<T>();
                    m._isReference  = Utilities::IsReference<T>();
                    m._name         = type.name();
                    m._size         = SizeOf<T>();
                    
                    m.Insert();
                    return m;
                }



                /** UTILITIES **/
                UtilitiesAPI bool Contains(const Field& field) const;
                UtilitiesAPI void Insert(const Metaclass& type, const string& name);

                UtilitiesAPI static const Metaclass& Get(const string& name);
                UtilitiesAPI static bool IsClass(const string& name);

                template<typename T> static bool IsClass()
                {
                    const auto& type = typeid(Dereference<T>::Class);
                    return IsClass(type.name());
                }



                /** OPERATORS **/


            private:
                
                /** DATA **/
                Set<Field*> _fields;
                uint        _id;
                bool        _isReference;
                bool        _isPointer;
                string      _name;
                uint        _size;



                /** CONSTRUCTOR **/
                UtilitiesAPI Metaclass();



                /** UTILITIES **/
                UtilitiesAPI void Insert() const;

        };

    }
}
