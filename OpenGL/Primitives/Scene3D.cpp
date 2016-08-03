#include "Interfaces/IRenderable.h"
#include "Primitives/Entity3D.h"
#include "Primitives/Scene3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** CONSTRUCTOR **/
        Scene3D::Scene3D()
        {

        }



        /** PUBLIC UTILITIES **/
        void Scene3D::Add(const IRenderableEntity& entity)
        {
            PerEntity data = 
            {
                entity.World().ToArray(),
                entity.Color(),
            };

            Set(&entity, data);
        }

    }
}