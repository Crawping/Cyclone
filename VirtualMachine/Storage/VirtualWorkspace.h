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
                VMAPI VirtualWorkspace();



                /** UTILITIES **/
                Literal& Access(uint id)                          { return _locals[ _locals.Contains(id) ? id : 0 ]; }
                const Literal& Access(uint id)              const { return _locals[ _locals.Contains(id) ? id : 0 ]; }
                Literal Get(uint id)                        const { return Access(id); }
                Literal Pop()                                     { return _workspace.Pop(); }
                void Push(const Literal& value)                   { _workspace.Push(value); }
                void Push(const Vector<Literal>& values)          { _workspace.Push(values); }
                //void Remove(uint count)                           { _workspace.Remove(0); }
                
                VMAPI void Set(uint id, const Literal& value);
                
            private:

                BST<uint, Literal>      _locals;
                Stack<Literal>          _workspace;
        };
    }
}
