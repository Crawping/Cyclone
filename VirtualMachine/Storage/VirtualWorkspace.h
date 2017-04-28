/* CHANGELOG
 * Written by Josh Grooms on 20170125
 */

#pragma once
#include "VMAPI.h"
#include "Collections/Stack.h"
#include "Virtual/Memory.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace VM
    {
        namespace Virtual
        {

            class VirtualWorkspace
            {
                public:

                    /** PROPERTIES **/
                    uint Count()                                        const { return _workspace.Count(); }
                    Variable& First()                                  { return _workspace.First(); }
                    const Variable& First()                      const { return _workspace.First(); }
                    Variable& Last()                                   { return _workspace.Last(); }
                    const Variable& Last()                       const { return _workspace.Last(); }



                    /** CONSTRUCTOR **/
                    VMAPI VirtualWorkspace();



                    /** UTILITIES **/
                    Variable& Access(uint id)                          { return _locals[ _locals.Contains(id) ? id : 0 ]; }
                    const Variable& Access(uint id)              const { return _locals[ _locals.Contains(id) ? id : 0 ]; }
                    Variable Get(uint id)                        const { return Access(id); }
                    Variable Pop()                                     { return _workspace.Pop(); }
                    void Push(const Variable& value)                   { _workspace.Push(value); }
                    void Push(const Vector<Variable>& values)          { _workspace.Push(values); }
                    //void Remove(uint count)                           { _workspace.Remove(0); }

                    VMAPI void Set(uint id, const Variable& value);

                private:

                    BST<uint, Variable>      _locals;
                    Stack<Variable>          _workspace;
            };

        }
    }
}
