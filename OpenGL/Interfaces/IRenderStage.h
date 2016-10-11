/* CHANGELOG
 * Written by Josh Grooms on 20161009
 */

#pragma once
#include "EnumerationsGL.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class IGraphicsBuffer;
        struct GraphicsSettings;

        class IRenderStage
        {
            public:
                /** PROPERTIES **/
                virtual const IGraphicsBuffer* Data()           const = 0;
                virtual const GraphicsSettings* Settings()      const = 0;
                virtual VertexTopologies Topology()             const = 0;

                /** DESTRUCTOR **/
                virtual ~IRenderStage() { }

                /** UTILITIES **/
                virtual void Render() = 0;
        };

    }
}
