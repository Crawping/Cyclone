/* CHANGELOG
 * Written by Josh Grooms on 20170201
 */



namespace Core.Primitives
{

    class List<T> : 
        interface  = ICollection;
    {
        uint Count
        {
            public get  { return _count; }
            private set { _count = value; }
        }
        @T First        { return 
        bool IsEmpty    { return Count == 0; }



        @T operator [](uint index);

        private uint _count;
        
    }

}
