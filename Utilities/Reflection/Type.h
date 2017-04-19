/* CHANGELOG
 * Written by Josh Grooms on 20170419
 */

#pragma once
#include "Utilities.h"
#include "Reflection/Metafunctions.h"



namespace Cyclone
{
    namespace Utilities
    {
        
        //#define typeof()
        using namespace Utilities;

        struct Metadata
        {

            /** DATA **/
            const uint      ID;
            const bool      IsReference;
            const bool      IsPointer;
            const string    Name;
            const uint      Size;



            /** STATIC CONSTRUCTOR **/
            template<typename T> static Metadata Create()
            {
                const auto& type = typeid(Dereference<T>::Class);
                return
                {
                    type.hash_code(),
                    Utilities::IsReference<T>(),
                    Utilities::IsPointer<T>(),
                    type.name(),
                    SizeOf<T>(),
                };
            }

        };



        class Type
        {
            public:
                
                /** PROPERTIES **/    
                uint ID()               const { return _data.ID; }
                bool IsReference()      const { return _data.IsReference; }
                bool IsPointer()        const { return _data.IsPointer; }
                const string& Name()    const { return _data.Name; }
                uint Size()             const { return _data.Size; }



                /** CONSTRUCTOR **/
                UtilitiesAPI Type(const Metadata& metadata);



                /** STATIC CONSTRUCTOR **/
                template<typename T> static Type Create()
                {
                    return Type( Metadata::Create<T>() );
                }



                /** UTILITIES **/
                //template<typename T> T Construct(T)
                //UtilitiesAPI void Construct();
                //UtilitiesAPI void HeapAllocate();
                //UtilitiesAPI void StackAllocate();


                /** OPERATORS **/


            private:
                
                /** DATA **/
                Metadata        _data;

        };


        
        



        //template<typename T>
        //struct TypeData<T>
        //{
        //    using Class             = T;
        //    const bool IsPointer    = false;
        //    const bool IsReference  = false;
        //    const string Name       = "";
        //    const uint Size         = sizeof(T);
        //};

        //template<typename T>
        //struct TypeData<T*>
        //{
        //    using Class             = T;
        //    const bool IsPointer    = true;
        //    const bool IsReference  = false;
        //    const uint Size         = sizeof(T);
        //};

        //template<typename T>
        //struct TypeData<T&>
        //{
        //    using Class             = T;
        //    const bool IsPointer    = false;
        //    const bool IsReference  = true;
        //    const uint Size         = sizeof(T);
        //};

    }
}
