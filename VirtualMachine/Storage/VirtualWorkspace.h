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
                uint Count()                                        const { return _workspace.Count(); }
                VirtualVariable& First()                                  { return _workspace.First(); }
                const VirtualVariable& First()                      const { return _workspace.First(); }
                VirtualVariable& Last()                                   { return _workspace.Last(); }
                const VirtualVariable& Last()                       const { return _workspace.Last(); }



                /** CONSTRUCTOR **/
                VMAPI VirtualWorkspace();



                /** UTILITIES **/
                VirtualVariable& Access(uint id)                          { return _locals[ _locals.Contains(id) ? id : 0 ]; }
                const VirtualVariable& Access(uint id)              const { return _locals[ _locals.Contains(id) ? id : 0 ]; }
                VirtualVariable Get(uint id)                        const { return Access(id); }
                VirtualVariable Pop()                                     { return _workspace.Pop(); }
                void Push(const VirtualVariable& value)                   { _workspace.Push(value); }
                void Push(const Vector<VirtualVariable>& values)          { _workspace.Push(values); }
                //void Remove(uint count)                           { _workspace.Remove(0); }

                VMAPI void Set(uint id, const VirtualVariable& value);

            private:

                BST<uint, VirtualVariable>      _locals;
                Stack<VirtualVariable>          _workspace;
        };
    }
}
