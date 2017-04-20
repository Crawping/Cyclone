/* CHANGELOG
 * Written by Josh Grooms on 20170419
 */

#pragma once
#include "Utilities.h"
#include "Collections/Set.h"
//#include "Reflection/Field.h"
#include "Reflection/Metafunctions.h"



namespace Cyclone
{
    namespace Utilities
    {
        
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
                    m._id = type.hash_code();
                    m._isReference = Utilities::IsReference<T>();
                    m._isPointer = Utilities::IsPointer<T>();
                    m._name = type.name();
                    m._size = SizeOf<T>();
                    
                    return m;
                }



                /** UTILITIES **/
                //UtilitiesAPI void Insert(const Field& field);
                //UtilitiesAPI void IsField(const Field& field);


                /** OPERATORS **/


            private:
                
                /** DATA **/
                //Set<Field*> _fields;
                uint        _id;
                bool        _isReference;
                bool        _isPointer;
                string      _name;
                uint        _size;


                //Metaclass() { }
        };

    }
}
