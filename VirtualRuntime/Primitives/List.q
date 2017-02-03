/* CHANGELOG
 * Written by Josh Grooms on 20170201
 */



namespace Core.Primitives
{

    class List<T> : 
        interfaces  = ICollection;
        T           = IDefaultable;
    {
        uint Count
        {
            default     { return 0; }
            public get  { return Value; }
            private set { Value = value; }
        }
        bool IsEmpty    { return Count == 0; }



        @T operator [](uint index);
        


    }

}
