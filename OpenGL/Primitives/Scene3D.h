/* CHANGELOG
 * Written by Josh Grooms on 20160724
 */

#pragma once
#include "Buffers/UniformBuffer.h"
#include "Buffers/UniformData.h"
#include "Buffers/UniformMap.h"
#include "GL/OpenGLAPI.h"
#include "Primitives/Entity3D.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class IRenderableEntity;


        class Scene3D : public UniformMap<const IRenderableEntity*, PerEntity>
        {
            public:

                const Transform& _viewProjection() const { return ViewProjection; }


                OpenGLAPI Scene3D();


                OpenGLAPI virtual void Add(const IRenderableEntity* entity);


                OpenGLAPI void BindResources() const override;

            private:

                Transform Camera;
                Transform ViewProjection;


                UniformBuffer<PerFrame> PerSceneBuffer;
                

        };
    }
}