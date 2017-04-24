#include "Metaclass.h"
#include "Utilities.h"
#include "Collections/BST.h"
#include "Meta/Field.h"
#include <memory>
#include <vector>



namespace Cyclone
{
    namespace Reflection
    {

        /** INTERNAL DATA **/
        //template<typename T>
        //struct Reference : public Class<T>
        //{
        //    public:

        //        template<typename ... U>
        //        Reference(U...) :
        //            _count(1),
        //            _data(new T(U...))
        //        {
        //            std::shared_ptr();
        //        }
        //        ~Reference()
        //        {
        //            if (--_count && _data)
        //                delete _data;
        //        }

        //    private:

        //        mutable uint    _count;
        //        T*              _data;
        //};



        static BST<string, Metaclass*> Classes;

        



        /** INTERNAL FUNCTIONS **/
        bool fieldcomparator(Field* const& x, Field* const& y)
        {
            return x->ID() < y->ID();
        }



        /** CONSTRUCTOR **/
        Metaclass::Metaclass() :
            Metaclass(Meta::Class<void>())
        {

        }
        Metaclass::Metaclass(Metaclass&& other) noexcept :
            _coreSize       (other._coreSize),
            _id             (other._id),
            _isConstant     (other._isConstant),
            _isReference    (other._isReference),
            _isPointer      (other._isPointer),
            _name           (other._name),
            _size           (other._size),
            _type           (other._type)
        {
            std::swap(_fields, other._fields);
            other._type = nullptr;
        }
        Metaclass::~Metaclass()
        {
            for (auto f : _fields)
                delete f;

            //Classes.Remove(_name);
            //if (_type) { delete _type; }
            //if (TypeCheck) { delete TypeCheck; }
            //if (DestroyType)    
            //{ 
            //    DestroyType->Invoke(_type);
            //    delete(DestroyType);
            //}
        }


        
        /** UTILITIES **/
        bool Metaclass::Contains(const Field& field) const
        {
            return _fields.Contains((Field* const) &field);
        }
        const Metaclass& Metaclass::Get(const string& name)
        {
            return *(Classes[name]);
        }
        void Metaclass::Insert(const Metaclass& type, const string& name)
        {
            Field* newfield = new Field(type, name);
        }
        bool Metaclass::IsClass(const string& name)
        {
            return Classes.Contains(name);
        }


        Metaclass& Metaclass::operator =(Metaclass&& other) noexcept
        {
            _coreSize       = other._coreSize;
            _id             = other._id;
            _isConstant     = other._isConstant;
            _isReference    = other._isReference;
            _isPointer      = other._isPointer;
            _name           = other._name;
            _size           = other._size;
            _type           = other._type;

            std::swap(_fields, other._fields);
            other._type = nullptr;
            return *this;
        }


        /** PRIVATE UTILITIES **/
        void Metaclass::Register(Metaclass* type)
        {
            Classes.Insert(type->Name(), type);
            //std::vector
        }

    }
}