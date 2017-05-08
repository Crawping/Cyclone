#include "Primitives/Array.h"



namespace Cyclone
{
    namespace Virtual
    {

        /** CONSTRUCTOR **/
        Array::Array(ReferenceTypes type, uint capacity):
            _data(capacity),
            _type(type)
        {

        }



        /** UTILITIES **/
        Number& Array::Access(Reference location)
        {
            static Number null(ReferenceTypes::Null);
            return location.Offset() < Count() ? _data(location.Offset()) : null;
        }
        void Array::Insert(Reference location, Number value)
        {
            _data.Insert(location.Offset(), value);
        }
        void Array::Insert(Reference location, const ICollection<Number>& values)
        {
            _data.Insert(location.Offset(), values);
        }


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