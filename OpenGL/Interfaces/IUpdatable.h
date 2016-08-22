/* CHANGELOG
 * Written by Josh Grooms on 20160821
 */

#pragma once
#include "GL/OpenGLAPI.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class OpenGLAPI IUpdatable
        {

            public:
                
                virtual bool NeedsUpdate() const = 0;
                
                virtual ~IUpdatable() { }

                virtual void Update() = 0;
                
        };
    }
}
