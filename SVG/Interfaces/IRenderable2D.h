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

        class IRenderable2D : public virtual IRenderable
        {
            public:
                
                virtual ~IRenderable2D() { }

                virtual void Fill()         const = 0;
                virtual void Stroke()       const = 0;
                virtual void Update()       const = 0;

        };

    }
}




