#include "Virtual/Class.h"



namespace Cyclone
{
    namespace Virtual
    {

        /** UTILITIES **/
        Reference& Class::Access(Reference location)
        {
            static Reference var;
            return var;
        }



        /** OPERATORS **/
        Class& Class::operator =(Class&& other) noexcept
        {
            _instances = std::move(other._instances);
            _methods = std::move(other._methods);
            _properties = std::move(other._properties);
            return *this;
        }
        Class& Class::operator =(const Class& other)
        {
                
            return *this;
        }

    }
}
