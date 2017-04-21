#include "Collections/BST.h"
#include "Reflection/Field.h"
#include "Reflection/Type.h"



namespace Cyclone
{
    namespace Utilities
    {

        /** INTERNAL DATA **/
        static BST<string, Metaclass> Classes;



        /** INTERNAL FUNCTIONS **/
        bool fieldcomparator(Field* const& x, Field* const& y)
        {
            return x->ID() < y->ID();
        }



        /** CONSTRUCTOR **/
        Metaclass::Metaclass()
        {
            _fields.Comparator(fieldcomparator);
        }
        Metaclass::~Metaclass()
        {
            for (auto f : _fields)
                delete f;
        }


        
        /** UTILITIES **/
        bool Metaclass::Contains(const Field& field) const
        {
            return _fields.Contains((Field* const) &field);
        }
        const Metaclass& Metaclass::Get(const string& name)
        {
            return Classes[name];
        }
        void Metaclass::Insert(const Metaclass& type, const string& name)
        {
            Field* newfield = new Field(type, name);
        }
        bool Metaclass::IsClass(const string& name)
        {
            return Classes.Contains(name);
        }



        /** PRIVATE UTILITIES **/
        void Metaclass::Register() const
        {
            Classes.Insert(Name(), *this);
        }

    }
}