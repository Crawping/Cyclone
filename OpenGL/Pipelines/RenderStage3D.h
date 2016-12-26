/* CHANGELOG
 * Written by Josh Grooms on 20161009
 */

#pragma once
#include "Buffers/CommandBuffer.h"
#include "Pipelines/RenderStage.h"



namespace Cyclone
{
    namespace OpenGL
    {

        template<typename T>
        struct RenderStage3D : public RenderStage
        {
            public:

                /** CONSTRUCTORS **/
                OpenGLAPI RenderStage3D();



                /** UTILITIES **/
                OpenGLAPI void Add(const T& command);
                OpenGLAPI void ClearBuffers()           override;
                OpenGLAPI void ClearCommands();
                OpenGLAPI void Render()                 const override;
                OpenGLAPI void Update();

            private:

                /** DATA **/
                CommandBuffer<T> Commands;

        };

    }
}
