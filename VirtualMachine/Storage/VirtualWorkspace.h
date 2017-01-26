/* CHANGELOG
 * Written by Josh Grooms on 20170125
 */

#pragma once
#include "VMAPI.h"
#include "Collections/Stack.h"
#include "Storage/Literal.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace VM
    {
        class VirtualWorkspace
        {
            public:

                /** PROPERTIES **/
                uint Count() const { return _variables.Count(); }



                /** UTILITIES **/
                Literal Get(uint index)                     const { return _variables(index); }
                void Remove(uint index, uint count = 1)     { _variables.Remove(index); }
                Literal Pop()                               { return _variables.Pop(); }
                void Push(const Literal& value)             { _variables.Push(value); }
                void Set(uint index, const Literal& value)  { _variables(index) = value; }


            private:

                Stack<Literal>  _variables;
        };
    }
}
