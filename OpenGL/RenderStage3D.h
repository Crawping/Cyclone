/* CHANGELOG
 * Written by Josh Grooms on 20161009
 */

#pragma once
#include "Buffers/CommandBuffer.h"
#include "Buffers/RenderStage.h"



namespace Cyclone
{
    namespace OpenGL
    {

        template<typename T>
        struct RenderStage3D : public RenderStage
        {
            public:

                /** PROPERTIES **/
                List<BufferBinding> Buffers() const override
                {
                    List<BufferBinding> buffers = RenderStage::Buffers();
                    buffers.Prepend({ Commands, 0 });
                    return buffers;
                }



                /** CONSTRUCTORS **/
                RenderStage3D()
                {

                }
                


                /** UTILITIES **/
                void Add(const T& command)  { Commands.Add(command); }
                void ClearCommands()        { Commands.Clear(); }
                void Update()               { Commands.Update(); }

                OpenGLAPI void Render() const;


            private:

                CommandBuffer<T>                          Commands;

        };

    }
}
