/* CHANGELOG 
 * Written by Josh Grooms on 20161204
 */

#pragma once
#include "TypeDefinitions.h"



namespace Cyclone
{
    namespace Utilities
    {

        struct IStructureMember
        {
            template<typename T> T& Value() = 0;
            template<typename T> const T& Value() const = 0;

            virtual ~IStructureMember() { }
        };








        struct StructureElement
        {
            public:

                template<typename T> void Set(T value)
                {

                }

            private:
                void* _value;
                void* _type;

                //template<typename T> T GetSet()

        };


        template<typename T>
        struct Type
        {
            static ulong ByteSize() const { return sizeof(T); }


            T* Cast(void* value) const { return (T*)value; }


        };



        class Structure
        {
            public:


            private:
                //BST<string, IStructureMember*>
        };

    }
}
