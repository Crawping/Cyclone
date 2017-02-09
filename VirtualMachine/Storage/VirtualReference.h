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

                VirtualReference& Type(VariableTypes value)
                {
                    _type = value;
                    return *this;
                }
                VirtualReference& Target(uint value)
                {
                    _target = value;
                    return *this;
                }
                VirtualReference& TargetType(uint value)
                {
                    _targetType = value;
                    return *this;
                }

                constexpr VirtualReference() :
                    _target(0),
                    _targetType(0)
                {

                }
                constexpr VirtualReference(VariableTypes type) :
                    _type(VariableTypes::Reference),
                    _target(0),
                    _targetType((uint)type)
                {

                }
                constexpr VirtualReference(VariableTypes type, uint targetType, uint target = 0) :
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
