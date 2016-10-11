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
        class GraphicsSettings;

        class IRenderingStage
        {
            public:

                virtual const GraphicsSettings* Settings()      const = 0;
                virtual VertexTopologies Topology()             const = 0;

                virtual ~IRenderingStage() { }

                virtual void Render() = 0;
        };


        class IRenderingStage3D : 
            public virtual IRenderingStage
        {
            public:
                /** PROPERTIES **/
                virtual const IGraphicsBuffer* PipelineData()   const = 0;

            

                /** DESTRUCTOR **/
                virtual ~IRenderingStage3D() { }



                /** UTILITIES **/
                virtual void Render() = 0;

        };


        class IRenderingStage2D
        {
            public:
                virtual const GraphicsSettings& Settings()      const = 0;

                virtual ~IRenderingStage2D() { }

                virtual void Render() = 0;
        };


    }
}
