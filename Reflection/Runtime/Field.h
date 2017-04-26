/* CHANGELOG
 * Written by Josh Grooms on 20170419
 */

#pragma once
#include "Runtime/Variable.h"



namespace Cyclone
{
    namespace Reflection
    {

        class Field : public Variable
        {

            public:

                uint ID()                   const { return _id; }
                const string& Name()        const { return _name; }
                const Metaclass& Type()     const { return _value.Type(); }
                const Variable& Value()     const { return _value; }

                ReflectionAPI Field& Value(const Variable& value);



                ReflectionAPI Field(const string& name);

            private:

                uint        _id;
                string      _name;
                Variable    _value;

        };
    }
}
