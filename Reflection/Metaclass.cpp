#include "Metaclass.h"
#include "Utilities.h"
#include "Collections/BST.h"
#include "Meta/Field.h"



namespace Cyclone
{
    namespace Reflection
    {

        /** INTERNAL DATA **/
        static BST<string, Metaclass> Classes;



        /** INTERNAL FUNCTIONS **/
        bool fieldcomparator(Field* const& x, Field* const& y)
        {
            return x->ID() < y->ID();
        }



        /** CONSTRUCTOR **/
        Metaclass::Metaclass() : 
            _coreSize(0),
            _id(0),
            _name(""),
            _size(0),
            _type(nullptr),
            TypeCheck(nullptr)
        {
            _fields.Comparator(fieldcomparator);
        }
        Metaclass::~Metaclass()
        {
            for (auto f : _fields)
                delete f;

            if (_type) { delete _type; }
            if (TypeCheck) { delete TypeCheck; }
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