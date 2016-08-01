#include "Interfaces/IRenderable.h"
#include "Primitives/Scene3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        Scene3D::Scene3D()
        {
            Transform projection = Transform::PerspectiveProjection(90, 960.0f / 540.0f, 1.0f, -1.0f);
            ViewProjection = projection * Camera;

            PerFrame frameData =
            {
                ViewProjection.ToArray(),
                Camera.Position(),
                0,
            };

            PerSceneBuffer.Set(0, frameData);
        }


        void Scene3D::Add(const IRenderableEntity* entity)
        {
            PerEntity data = 
            {
                entity->World().ToArray(),
                entity->Color(),
            };

            Set(entity, data);
        }


        void Scene3D::BindResources() const
        {
            //PerSceneBuffer.Bind(1);
        }
    }
}