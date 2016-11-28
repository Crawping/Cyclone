/* CHANGELOG 
 * Written by Josh Grooms on 20161125
 */

#pragma once
#include "Event.h"
#include "Buffers/UniformMap.h"
#include <set>



namespace Cyclone
{
    namespace OpenGL
    {

        template<typename T>
        struct ResourceKey
        {
            public:
                int Resolve() const;

            private:

                
        };


        template<typename T>
        class ResourceLibrary : public UniformMap<uint, T>
        {
            public:
                
                /** CONSTRUCTOR **/
                ResourceLibrary() 
                {

                }


                uint Add(const T& resource)
                {
                    uint idx = 0;
                    for (const T& d : Data().Values())
                        if (resource == d)
                            return idx;
                        else
                            idx++;
                    
                    idx = 0;
                    while (Contains(idx)) { idx++; }
                    Set(idx, resource);
                    return idx;
                }

            //private:
                
        };
    }
}
