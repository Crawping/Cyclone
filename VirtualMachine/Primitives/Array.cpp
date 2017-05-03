#include "Primitives/Array.h"



namespace Cyclone
{
    namespace Virtual
    {

        /** CONSTRUCTOR **/
        Array::Array(ReferenceTypes type):
            _type(type)
        {

        }



        /** UTILITIES **/
        Number& Array::Access(Reference location)
        {
            static Number null(ReferenceTypes::Null);
            return location.Offset() < Count() ? _data(location.Offset()) : null;
        }
        //template<> Reference& Array::Access<Reference>(Reference location)
        //{
        //    bool isValid = 
        //        (location.Type() == ReferenceTypes::Reference)  && 
        //        (location.Offset() < _data.Count());

        //    



        //}
        //template<> Number& Array::Access<Number>(Reference location)
        //{

        //}


        //Array::Array(uint id) : _id(id) { }

        //Array Array::Calculate(Instructions operation, const Array& other)
        //{
        //    return Array();
        //}
        //Reference& Array::Get(uint index)
        //{
        //    return _data(index);
        //}
        //void Array::Set(uint index, const Reference& value)
        //{
        //    if (index >= Count()) { return; }
        //    _data(index) = value;
        //}

    }
}