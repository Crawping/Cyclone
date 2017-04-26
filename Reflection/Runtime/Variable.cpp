#include "Runtime/Variable.h"



namespace Cyclone
{
    namespace Reflection
    {

        /** CONSTRUCTORS **/
        Variable::Variable() : 
            Data(new Null<void>())
        {

        }
        Variable::Variable(Variable&& other) :
            Data(other.Data)
        {
            other.Data = nullptr;
        }
        Variable::Variable(const Variable& other) :
            Data(other.Data->Copy())
        {

        }
        Variable::~Variable()
        {
            if (Data) delete Data;
        }



        /** OPERATORS **/
        Variable& Variable::operator =(Variable&& other)
        {
            std::swap(Data, other.Data);
            return *this;
        }
        Variable& Variable::operator =(const Variable& other)
        {
            if (Data) delete Data;
            Data = other.Data->Copy();
            return *this;
        }
        bool Variable::operator ==(const Variable& other) const
        {
            return *Data == *(other.Data);
        }
        bool Variable::operator !=(const Variable& other) const
        {
            return !(operator ==(other));
        }

    }
}