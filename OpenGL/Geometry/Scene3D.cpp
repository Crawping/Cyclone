#include "Interfaces/IRenderable.h"
#include "Geometry/Scene3D.h"
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
            if (entity.Indices().IsEmpty())
                Buffers[entity.Topology()].Add(entity);
            else
                IndexedBuffers[entity.Topology()].Add(entity);
        }
        void Scene3D::Remove(const IRenderableEntity& entity)
        {
            if (entity.Indices().IsEmpty())
                Buffers[entity.Topology()].Remove(entity);
            else
                IndexedBuffers[entity.Topology()].Remove(entity);
        }
        void Scene3D::Render() const
        {
            for (const auto& kvp : Buffers)
            {
                kvp.second.Bind();
                glMultiDrawArraysIndirect(kvp.first, 0, kvp.second.Count(), 0);
            }

            for (const auto& kvp : IndexedBuffers)
            {
                kvp.second.Bind();
                glMultiDrawElementsIndirect(kvp.first, GL_UNSIGNED_INT, 0, kvp.second.Count(), 0);
            }
        }
        void Scene3D::Update()
        {
            for (auto& kvp : Buffers)
                kvp.second.Update();
            for (auto& kvp : IndexedBuffers)
                kvp.second.Update();
        }

        void Scene3D::Update(const IRenderableEntity& entity)
        {
            if (entity.Indices().IsEmpty())
                Buffers[entity.Topology()].Update(entity);
            else
                IndexedBuffers[entity.Topology()].Update(entity);
        }

    }
}