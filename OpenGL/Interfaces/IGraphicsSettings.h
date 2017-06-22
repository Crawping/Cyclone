/* CHANGELOG
 * Written by Josh Grooms on 20170619
 */

#pragma once
#include "EnumerationsGL.h"
#include "Resources/Resource.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class IGraphicsPipeline;


        struct IGraphicsSettings
        {

            //virtual bool IsBlendEnabled()                   const = 0;
            //virtual bool IsDepthStencilEnabled()            const = 0;
            //virtual bool IsStencilTestEnabled()             const = 0;

            //virtual CullingModes CullingMode()              const = 0;
            //virtual const IGraphicsPipeline* Pipeline()     const = 0;


            virtual ~IGraphicsSettings() { }
            
        };
    }
}
