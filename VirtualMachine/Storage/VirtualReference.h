/* CHANGELOG
 * Written by Josh Grooms on 20170207
 */

#pragma once
#include "Storage/VirtualVariable.h"



namespace Cyclone
{
    namespace VM
    {
        class VirtualReference
        {
            public:

                constexpr VariableTypes Type()  const { return _type; }
                constexpr uint Target()         const { return _target; }
                constexpr uint TargetType()     const { return _targetType; }


                constexpr VirtualReference() :
                    _target(0),
                    _targetType(0)
                {

                }
                constexpr VirtualReference(VariableTypes type, uint targetType, uint target) :
                    _type(type),
                    _target(target),
                    _targetType(targetType)
                {

                }

                constexpr operator VirtualVariable() const { return VirtualVariable(_type, _targetType, _target); }

            private:

                VariableTypes   _type;
                uint            _target;
                uint            _targetType;
        };
    }
}
