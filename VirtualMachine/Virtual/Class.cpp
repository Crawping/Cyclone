#include "Virtual/Class.h"



namespace Cyclone
{
    namespace VM
    {
        namespace Virtual
        {

            /** CONSTRUCTORS **/




            /** UTILITIES **/
            Variable& Class::Access(Address location)
            {
                //return _properties[location.Offset()].Get(;
            }
            const Vector<Instruction>& Class::Call(Address location) const
            {

            }

            //const Vector<Instruction>& Class::Call(uint method)                     const
            //{
            //    return _methods[ _methods.Contains(method) ? method : 0 ].Logic();
            //}
            //void Class::Delete(uint instance)
            //{
            //    if (ID() == 0 || !_instances.Contains(instance)) { return; }
            //    for (auto& kvp : _properties)
            //        kvp.Value.Delete(instance);
            //}
            //Variable& Class::Get(uint object, uint property)
            //{
            //    return _properties[ _properties.Contains(property) ? property : 0 ].Get(object);
            //}
            //void Class::Insert(Function&& function)
            //{
            //    if (ID() == 0 || function.ID() == 0) { return; }
            //    _methods.Insert(function.ID(), std::forward<Function>(function));
            //}
            //void Class::Insert(Property&& property)
            //{
            //    if (ID() == 0) { return; }
            //    _properties.Insert(property.ID(), std::forward<Property>(property));
            //}
            //bool Class::IsMethod(uint id)                                           const { return _methods.Contains(id); }
            //bool Class::IsOfType(const Variable& object)                            const
            //{
            //    return object.IsObject() && (object.FirstHalf() == ID());
            //}
            //void Class::Set(uint instance, uint property, const Variable& value)
            //{
            //    if (ID() == 0 || !_properties.Contains(property)) { return; }
            //    _instances.Insert(instance);
            //    _properties[property].Set(instance, value);
            //}
            //const VirtualReference& Class::TypeOf(uint property)                    const
            //{
            //    return _properties[ _properties.Contains(property) ? property : 0 ].Type();
            //}



            /** OPERATORS **/
            //Class& Class::operator =(Class&& other)
            //{
            //    //_type = other._type;
            //    _instances = std::move(other._instances);
            //    _methods = std::move(other._methods);
            //    _properties = std::move(other._properties);

            //    return *this;
            //}
        }
    }
}
