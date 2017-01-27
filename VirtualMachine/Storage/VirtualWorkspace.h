/* CHANGELOG
 * Written by Josh Grooms on 20170125
 */

#pragma once
#include "VMAPI.h"
#include "Collections/Stack.h"
#include "Storage/VirtualMemory.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace VM
    {
        class VirtualWorkspace
        {
            public:

                /** PROPERTIES **/
                uint Count()                                const { return _workspace.Count(); }
                Literal& First()                                  { return _workspace.First(); }
                const Literal& First()                      const { return _workspace.First(); }
                Literal& Last()                                   { return _workspace.Last(); }
                const Literal& Last()                       const { return _workspace.Last(); }



                /** CONSTRUCTOR **/
                VMAPI VirtualWorkspace(const VirtualMemory& memory);



                /** UTILITIES **/
                Literal& Access(uint index)                       { return _workspace(index); }
                Literal Get(uint index)                     const { return _workspace(index); }
                void Remove(uint index, uint count = 1)           { _workspace.Remove(index); }
                Literal Pop()                                     { return _workspace.Pop(); }
                void Push(const Literal& value)                   { _workspace.Push(value); }
                void Set(uint index, const Literal& value)        { _workspace(index) = value; }


                VMAPI Literal operator ()(uint index)       const;
                
            private:

                BST<uint, Literal>      _locals;
                const VirtualMemory*    _memory;
                Stack<Literal>          _workspace;
        };
    }
}
