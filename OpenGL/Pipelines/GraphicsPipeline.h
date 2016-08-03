/* CHANGELOG
 * Written by Josh Grooms on 20160607
 */

#pragma once
#include "EnumerationsGL.h"
#include "Interfaces/IBindable.h"
#include "Interfaces/IRenderable.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/UniformData.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class FrameBuffer;
        class Shader;

        /// <summary> An abstract base class that represents the rendering or compute pipelines used by GPUs. </summary>
        class GraphicsPipeline : public IBindable
        {

            public:

                /** PROPERTIES **/
                /// <summary> Gets the unique numeric identifier (or 'Name' in OpenGL jargon) associated with this shader pipeline. </summary>
                uint ID()                               const override { return _id; }



                /** DESTRUCTOR **/
                /// <summary> Destroys the OpenGL shader pipeline program. </summary>
		        OpenGLAPI virtual ~GraphicsPipeline();



                /** BINDING METHODS **/
                /// <summary> Activates this rendering pipeline and any stored uniform variables for immediate use on the GPU. </summary>
                /// <param name="slot"> A parameter of the <see cref="IBindable"/> interface that has no effects here. </param>
		        OpenGLAPI void Bind(int slot = 0)       const override;
		        /// <summary> Activates this rendering pipeline for immediate use on the GPU. </summary>
                /// <param name="slot"> A parameter of the <see cref="IBindable"/> interface that has no effects here. </param>
		        OpenGLAPI void BindEntity(int slot = 0) const override;
		        /// <summary> Activates any stored uniform shader variables for immediate use on the GPU. </summary>
                OpenGLAPI void BindResources()          const override { }
		        /// <summary> Deactivates this rendering pipeline and any associated resources on the GPU. </summary>
                OpenGLAPI void Unbind()                 const override;
		        /// <summary> Deactivates this rendering pipeline on the GPU. </summary>
		        OpenGLAPI void UnbindEntity()           const override;
		        /// <summary> Deactivates any resources associated with this rendering pipeline on the GPU. </summary>
                OpenGLAPI void UnbindResources()        const override { }
                
            protected:
            
                /** CONSTRUCTOR **/
                /// <summary> Constructs a new OpenGL shader pipeline to which individual shader programs can be attached. </summary>
		        OpenGLAPI GraphicsPipeline();



                /** UTILITIES **/
                /// <summary> Combines separate shader programs into a single executable pipeline and validates the results. </summary>
                /// <returns> A Boolean <c>true</c> if linking is successful, or <c>false</c> otherwise. </returns>
                OpenGLAPI virtual bool Link();
                /// <summary> Retrieves error information that was logged while attempting to link shader programs. </summary>
                OpenGLAPI virtual string ReportShaderLog() const;

            private:

                /** PROPERTY DATA **/
                uint _id;

        };
    }
}
