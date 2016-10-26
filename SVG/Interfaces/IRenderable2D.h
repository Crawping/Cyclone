/* CHANGELOG
 * Written by Josh Grooms on 20161012
 */

#pragma once
#include "Interfaces/IRenderable.h"



namespace Cyclone
{
    namespace { using namespace OpenGL; }
    namespace SVG
    {

        template<typename T> class IRenderable2D :
            public virtual IRenderable3D<T>
        {
            public:
                
                /** PROPERTIES **/
                //virtual Vector2 Offset()    const = 0;
                //virtual Vector2 Size()      const = 0;

                virtual ~IRenderable2D() { }

                virtual void Fill()         const = 0;
                virtual void Stroke()       const = 0;
                virtual void Update()       const = 0;

        };

    }
}




