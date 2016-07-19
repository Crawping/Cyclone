/* CHANGELOG
 * Written by Josh Grooms on 20160607
 */

#pragma once
#include "EnumerationsGL.h"
#include "Interfaces/IBindable.h"
#include "Interfaces/IRenderable.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/UniformBuffers.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class FrameBuffer;

        class GraphicsPipeline : public IBindable
        {
            public:

                /** PROPERTIES **/

                uint ID()                                       const override { return _id; }
		        virtual FrameBuffer* RenderTarget()		        const = 0;

		        virtual void RenderTarget(FrameBuffer* target)  = 0;



                /** DESTRUCTOR **/
		        OpenGLAPI virtual ~GraphicsPipeline();



                /** BINDING METHODS **/
                /// <summary> Activates this rendering pipeline and any stored uniform variables for immediate use on the GPU. </summary>
		        OpenGLAPI void Bind(int slot = 0)       const override;
		        /// <summary> Activates this rendering pipeline for immediate use on the GPU. </summary>
		        OpenGLAPI void BindEntity(int slot = 0) const override;
		        /// <summary> Activates any stored uniform shader variables for immediate use on the GPU. </summary>
                void BindResources()                    const override { }
		        /// <summary> Deactivates this rendering pipeline and any associated resources on the GPU. </summary>
                OpenGLAPI void Unbind()                 const override;
		        /// <summary> Deactivates this rendering pipeline on the GPU. </summary>
		        OpenGLAPI void UnbindEntity()           const override;
		        /// <summary> Deactivates any resources associated with this rendering pipeline on the GPU. </summary>
                void UnbindResources()                  const override { }



                /** RENDERING UTILITIES **/
                virtual void Execute()                              = 0;
                virtual void Input(const IRenderableEntity& entity) = 0;
                virtual void Input(const PerFrame& frameData)       = 0;
                virtual void Reset()                                = 0;
		
            protected:

                /** CONSTRUCTOR **/
		        OpenGLAPI GraphicsPipeline();
        
                /// <summary> Retrieves and posts error information that was logged while attempting to link shader programs. </summary>
                OpenGLAPI virtual string ReportShaderLog() const;

            private:

                /** PROPERTY DATA **/
                uint _id;

        };
    }
}