#include "Virtual/Function.h"



namespace Cyclone
{
    namespace Virtual
    {

        /** PROPERTIES **/
        Function& Function::Logic(const ICollection<Instruction>& value)
        {
            _logic = Vector<Instruction>(value, 0, value.Count());
            return *this;
        }



        /** CONSTRUCTOR **/
        //Function::Function(const Vector<Instruction>& logic) :
        //    _logic(logic, 0, logic.Count())
        //{

        //}
    }
}