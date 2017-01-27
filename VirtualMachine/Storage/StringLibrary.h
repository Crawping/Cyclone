/* CHANGELOG
 * Written by Josh Grooms on 20170127
 */

#pragma once
#include "VMAPI.h"
#include "Collections/BST.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace VM
    {
        class StringLibrary
        {
            public:

                /** PROPERTIES **/
                uint Count() const { return _strings.Count(); }



                /** CONSTRUCTOR **/
                VMAPI StringLibrary();



                /** UTILITIES **/
                VMAPI void Clear();
                VMAPI bool Contains(uint id)                const;
                VMAPI bool Contains(const string& string)   const;
                VMAPI const string& Find(uint id)           const;
                VMAPI uint Find(const string& string)       const;
                VMAPI uint Insert(const string& string);
                VMAPI void Remove(uint id);
                VMAPI void Remove(const string& string);



                /** OPERATORS **/
                const string& operator [](uint id)      const { return Find(id); }
                uint operator [](const string& string)  const { return Find(string); }

            private:

                BST<string, uint>   _ids;
                BST<uint, string>   _strings;

        };
    }
}
