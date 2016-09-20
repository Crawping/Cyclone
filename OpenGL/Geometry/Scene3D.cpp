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
        void Scene3D::Add(const IRenderable3D<Vertex::Standard>& entity)
        {
            if (entity.Indices().IsEmpty())
                Buffers[entity.Topology()].Add(entity);
            else
                IndexedBuffers[entity.Topology()].Add(entity);
        }
        void Scene3D::Add(const IRenderable2D<string>& entity)
        {
            PathBuffer.insert(&entity);
        }
        void Scene3D::Remove(const IRenderable3D<Vertex::Standard>& entity)
        {
            if (entity.Indices().IsEmpty())
                Buffers[entity.Topology()].Remove(entity);
            else
                IndexedBuffers[entity.Topology()].Remove(entity);
        }
        void Scene3D::Remove(const IRenderable2D<string>& entity)
        {
            PathBuffer.erase(&entity);
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
                glMultiDrawElementsIndirect(kvp.first, NumericFormats::UInt, 0, kvp.second.Count(), 0);
            }

            if (PathBuffer.size())
            {
                glStencilMask(~0);
                glEnable(GL_STENCIL_TEST);
                glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
                glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);

                for (const auto* p : PathBuffer)
                    p->Render();

                glDisable(GL_STENCIL_TEST);
            }
        }
        void Scene3D::Update()
        {
            for (auto& kvp : Buffers)
                kvp.second.Update();
            for (auto& kvp : IndexedBuffers)
                kvp.second.Update();
        }

        void Scene3D::Update(const IRenderable3D<Vertex::Standard>& entity)
        {
            if (entity.Indices().IsEmpty())
                Buffers[entity.Topology()].Update(entity);
            else
                IndexedBuffers[entity.Topology()].Update(entity);
        }

    }
}