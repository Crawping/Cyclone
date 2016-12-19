/* CHANGELOG
 * Written by Josh Grooms on 20161009
 */

#pragma once
#include "EnumerationsGL.h"
#include "Interfaces/IGraphicsBuffer.h"



namespace Cyclone
{
    namespace OpenGL
    {
        struct GraphicsSettings;

        class IRenderStage
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets a list of binding configurations for the GPU resource buffers used by the rendering stage. </summary>
                virtual List<BufferBinding> Buffers()           const = 0;
                virtual const GraphicsSettings& Settings()      const = 0;
                virtual VertexTopologies Topology()             const = 0;

                /** DESTRUCTOR **/
                virtual ~IRenderStage() { }

                /** UTILITIES **/
                virtual void Render()                           const = 0;
        };

    }
}
