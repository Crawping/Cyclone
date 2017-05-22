/* CHANGELOG
 * Written by Josh Grooms on 20170428
 */

#pragma once
#include "Collections/Vector.h"
#include "Collections/String.h"
#include "Primitives/Array.h"
#include "Primitives/Number.h"
#include "Storage/Reference.h"
#include "Virtual/Class.h"
#include "Virtual/Function.h"



namespace Cyclone
{
    namespace Virtual
    {

        class StackFrame
        {
            public:

                /** PROPERTIES **/
                Vector<Reference, 128>& Inputs()    { return Input; }
                Vector<Reference, 128>& Outputs()   { return Output; }

                VMAPI StackFrame& Inputs(const Vector<Reference, 128>& value);
                VMAPI StackFrame& Outputs(const Vector<Reference, 128>& value);



                /** UTILITIES **/
                template<typename T>
                VMAPI T& Access(Reference location);

                template<typename T>
                VMAPI void Insert(Reference location, T& value);

                VMAPI void Delete(Reference location);
                    
                VMAPI void Reset();

            private:

                /** DATA **/
                Vector<Array*,      256>  Arrays;
                Vector<Class*,      256>  Classes;
                Vector<Function*,   256>  Functions;
                Vector<Number,      256>  Numbers;
                Vector<String*,     256>  Strings;

                Vector<Reference,   128>  Input;
                Vector<Reference,   256>  Local;
                Vector<Reference,   128>  Output;

        };



        /** TEMPLATE SPECIALIZATIONS **/
        template<> VMAPI Array& StackFrame::Access<Array>(Reference location);
        template<> VMAPI Class& StackFrame::Access<Class>(Reference location);
        template<> VMAPI Function& StackFrame::Access<Function>(Reference location);
        template<> VMAPI Number& StackFrame::Access<Number>(Reference location);
        template<> VMAPI Reference& StackFrame::Access<Reference>(Reference location);
        template<> VMAPI String& StackFrame::Access<String>(Reference location);

        template<> VMAPI void StackFrame::Insert<Array>(Reference location, Array& value);
        template<> VMAPI void StackFrame::Insert<Class>(Reference location, Class& value);
        template<> VMAPI void StackFrame::Insert<Function>(Reference location, Function& value);
        template<> VMAPI void StackFrame::Insert<Number>(Reference location, Number& value);
        template<> VMAPI void StackFrame::Insert<Reference>(Reference location, Reference& value);
        template<> VMAPI void StackFrame::Insert<String>(Reference location, String& value);

    }
}
