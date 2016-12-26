/* CHANGELOG
 * Written by Josh Grooms on 20161009
 */

#pragma once
#include "EnumerationsGL.h"
#include "Collections/List.h"
#include "Interfaces/IGraphicsBuffer.h"



namespace Cyclone
{
    namespace OpenGL
    {
        struct GraphicsSettings;

        /// <summary> An interface that represents a single indivisible stage of a rendering process. </summary>
        /// <remarks>
        ///     A rendering stage is defined here as the most basic single element of some rendering procedure. It is intended to contain
        ///     all of the information necessary to completely setup and execute the rendering of geometric data on the GPU. Specifically, 
        ///     this includes (but is not necessarily limited to): GPU resource buffer configurations, the rendering pipeline to be used, 
        ///     blending configurations, depth/stencil testing configurations, and the primitive topology of the geometry to be rendered.
        /// </remarks>
        class IRenderStage
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets a list of binding configurations for the GPU resource buffers used by the rendering stage. </summary>
                virtual List<BufferBinding> Buffers()                   const = 0;
                /// <summary> Gets the GPU configuration used to execute the rendering stage. </summary>
                virtual const GraphicsSettings& Settings()              const = 0;
                /// <summary> Gets the primitive topology of the geometry to be rendered by the stage. summary>
                virtual VertexTopologies Topology()                     const = 0;

                /** DESTRUCTOR **/
                /// <summary> Destroys any specially allocated resources that are held by the rendering stage. </summary>
                virtual ~IRenderStage() { }

                /** UTILITIES **/
                /// <summary> Adds a resource buffer binding to the list of those used by the rendering stage. </summary>
                /// <param name="binding"> A binding configuration containing the buffer and its associated attachment point. </param>
                virtual void Add(const BufferBinding& buffer)           = 0;
                /// <summary> Adds a collection of buffer bindings to the list of those used by the rendering stage. </summary>
                /// <param name="bindings"> A list of binding configurations containing the buffers and their associated attachment points. </param>
                virtual void Add(const List<BufferBinding>& buffers)    = 0;
                /// <summary> Resets the internal list of buffer bindings to its default configuration. </summary>
                virtual void ClearBuffers()                             = 0;
                /// <summary> Executes the rendering logic needed to display the contents of the stage's resource buffers. </summary>
                virtual void Render()                                   const = 0;
        };

    }
}
