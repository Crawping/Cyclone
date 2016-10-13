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
                
                virtual ~IRenderable2D() { }

                //virtual void Render() const = 0;

                virtual void Fill() const = 0;
                virtual void Stroke() const = 0;

        };

    }
}




