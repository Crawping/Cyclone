#include "Interfaces/IRenderable.h"
#include "Primitives/Scene3D.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** CONSTRUCTOR **/
        Scene3D::Scene3D() : 
            NeedsUpdate(false)
        {

        }



        /** PUBLIC UTILITIES **/
        void Scene3D::Add(const IRenderableEntity& entity)
        {
            EntitySet.insert(&entity);
            NeedsUpdate = true;
        }
        void Scene3D::Bind(int slot) const
        {
            Vertices.Bind();
            Commands.Bind();
            Entities.Bind();
        }
        void Scene3D::Remove(const IRenderableEntity& entity)
        {
            if (!EntitySet.count(&entity)) { return; }
            EntitySet.erase(&entity);
            NeedsUpdate = true;
        }
        void Scene3D::Update()
        {
            if (!NeedsUpdate) { return; }
            
            Commands.Clear();
            Entities.Clear();
            Vertices.Clear();

            for (auto* entity : EntitySet)
            {
                AddCommand(*entity);
                AddEntity(*entity);
                AddVertices(*entity);
            }

            Commands.Update();
            Entities.Update();
            Vertices.Update();

            NeedsUpdate = false;
        }



        /** PRIVATE UTILITIES **/
        void Scene3D::AddCommand(const IRenderableEntity& entity)
        {
            DrawCommand cmd =
            {
                entity.Vertices().Count(),
                1,
                Vertices.Count(),
                Commands.Count(),
            };
            Commands.Add(cmd);
        }
        void Scene3D::AddEntity(const IRenderableEntity& entity)
        {
            PerEntity data = 
            {
                entity.World().ToArray(),
                entity.Color(),
            };
            Entities.Add(data);
        }
        void Scene3D::AddVertices(const IRenderableEntity& entity)
        {
            const Array<Vertex>& vertices = entity.Vertices();
            for (uint a = 0; a < vertices.Count(); a++)
                Vertices.Add(vertices(a));
        }
    }
}