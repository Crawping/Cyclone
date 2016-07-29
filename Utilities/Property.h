#pragma once



template<typename T>
struct Property
{
    private:
        typedef T (*GetAccessor)(void);
        typedef void (*SetAccessor)(T& value);

        GetAccessor _get;
        SetAccessor _set;
        T Value;


        constexpr T DefaultGet()    { return _value; }
        void DefaultSet(T& value)   { Value = value; }


    public

        constexpr T Get()           { return _get(); }
        void Set(T& value)          { return _set(value); }
        


        /** CONSTRUCTOR **/
        constexpr Property(GetAccessor get = DefaultGet, SetAccessor set = DefaultSet) :
            _get(get),
            _set(set)
        {

        }
        
};
