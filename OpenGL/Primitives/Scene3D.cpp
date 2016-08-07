#include "Interfaces/IRenderable.h"
#include "Primitives/Scene3D.h"
#include "Spatial/Transform.h"



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

            Array<Vertex> vertices = entity.Vertices();
            DrawCommand command =
            {
                vertices.Count(),
                1,
                Vertices.Count(),
                Commands.Count(),
            };

            EntityIndices[&entity] = Entities.Count();
            Entities.Add(data);
            Commands.Add(command);
            
            for (uint a = 0; a < vertices.Count(); a++)
                Vertices.Add(vertices(a));
        }
        void Scene3D::Bind(int slot) const
        {
            Vertices.Bind();
            Commands.Bind();
            Entities.Bind();
        }
        void Scene3D::Update()
        {
            Commands.Update();
            Entities.Update();
            Vertices.Update();
        }

    }
}