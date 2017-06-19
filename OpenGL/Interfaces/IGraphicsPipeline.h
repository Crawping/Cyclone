/* CHANGELOG
 * Written by Josh Grooms on 20170619
 */

#pragma once
#include "Interfaces/IBindable.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class IGraphicsPipeline: public IBindable
        {
            public:

                virtual ~IGraphicsPipeline() { }

        };
    }
}
