/* CHANGELOG
 * Written by Josh Grooms on 20170419
 */

#pragma once
#include "TypeDefinitions.h"
#include "Reflection/Type.h"



namespace Cyclone
{
    namespace Utilities
    {

        class Field
        {
            public:

                uint ID()                   const { return _id; }
                const string& Name()        const { return _name; }
                uint Offset()               const { return _offset; }
                const Metaclass& Type()     const { return _type; }

                Field(const Metaclass& type, const string& name) :
                    _id(0),
                    _name(""),
                    _offset(0),
                    _type(type)
                {

                }


            private:

                uint        _id;
                string      _name;
                uint        _offset;
                Metaclass   _type;

        };
    }
}
