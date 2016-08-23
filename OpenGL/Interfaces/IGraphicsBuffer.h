/* CHANGELOG
 * Written by Josh Grooms on 20160823
 */

#pragma once
#include "GL/OpenGLAPI.h"
#include "Interfaces/IBindable.h"
#include "Interfaces/IUpdatable.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class OpenGLAPI IGraphicsBuffer : public IBindable, public IUpdatable
        {

            public:
                virtual uint Count()        const = 0;

                virtual bool IsEmpty()      const { return Count() == 0; }

                virtual ~IGraphicsBuffer()  { }
                
                virtual void Clear()        = 0;

        };
    }
}
