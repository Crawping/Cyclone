/* CHANGELOG
 * Written by Josh Grooms on 20170702
 */

#pragma once
#include "Collections/Set.h"



namespace Cyclone
{
    namespace Utilities
    {

        template<typename T> struct Graph<T>
        {
            private:

                //List<Node<T>>
                //List<Node<T>>   _nodes;
                Set<Node<T>>    _nodes;

            public:

                Graph& Comparator(Function<bool, const T&, const T&> value)
                {
                    _nodes.Comparator(value);
                    return *this;
                }


                Graph()
                {

                }



                /** UTILITIES **/
                template<typename U>
                Graph& Insert(U&& value)
                {

                    return *this;
                }



        };

    }
}
