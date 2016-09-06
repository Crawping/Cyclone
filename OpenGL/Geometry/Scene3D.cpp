#include "Interfaces/IRenderable.h"
#include "Geometry/Scene3D.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** CONSTRUCTOR **/
        Scene3D::Scene3D() : 
            _needsUpdate(false)
        {

        }



        /** PUBLIC UTILITIES **/
        void Scene3D::Add(const IRenderableEntity& entity)
        {
            EntitySet.insert(&entity);
            _needsUpdate = true;
        }
        void Scene3D::Remove(const IRenderableEntity& entity)
        {
            if (!EntitySet.count(&entity)) { return; }
            EntitySet.erase(&entity);
            _needsUpdate = true;
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
            //if (!_needsUpdate) { return; }            

            //for (auto& kvp : Buffers)
            //    kvp.second.Clear();
            //for (auto& kvp : IndexedBuffers)
            //    kvp.second.Clear();

            //for (auto* entity : EntitySet)
            //{
            //    if (entity->Indices().IsEmpty())
            //        Buffers[entity->Topology()].Add(*entity);
            //    else
            //        IndexedBuffers[entity->Topology()].Add(*entity);
            //}

            for (auto& kvp : Buffers)
                kvp.second.Update();
            for (auto& kvp : IndexedBuffers)
                kvp.second.Update();

            _needsUpdate = false;
        }

        void Scene3D::Update(const IRenderableEntity& entity)
        {
            if (!EntitySet.count(&entity)) { return; }
            if (entity.Indices().IsEmpty())
                Buffers[entity.Topology()].Update(entity);
            else
                IndexedBuffers[entity.Topology()].Update(entity);

        }

    }
}