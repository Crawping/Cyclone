#include "RenderStage.h"
#include "Collections/List.h"
#include "Interfaces/IRenderable.h"
#include "Geometry/Scene3D.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {





        List<IRenderStage*> Scene3D::Stages() const
        {
            //for (uint a = 0; a < Stages3D.Count(); a++)
            //    delete Stages3D(a);

            //Stages3D.Clear();

            //for (const auto& kvp : Buffers)
            //    Stages3D.Append(new RenderStage3D(kvp.first, &kvp.second, nullptr));

            //for (const auto& kvp : IndexedBuffers)
            //    Stages3D.Append(new IndexedRenderStage3D(kvp.first, &kvp.second, nullptr));

            return Stages3D;
        }



        /** CONSTRUCTOR **/
        Scene3D::Scene3D()
        {

        }
        Scene3D::~Scene3D()
        {
            for (uint a = 0; a < Stages3D.Count(); a++)
                delete Stages3D(a);
        }




        /** PUBLIC UTILITIES **/
        void Scene3D::Add(const IRenderable3D<Vertex::Standard>& entity)
        {
            if (entity.Indices().IsEmpty())
                Buffers[entity.Topology()].Add(entity);
            else
                IndexedBuffers[entity.Topology()].Add(entity);
        }
        void Scene3D::Add(const IRenderable2D<float>& entity)
        {
            if (PathBuffer.count(&entity)) { return; }

            PathBuffer.insert(&entity);

            //const auto& components = entity.Components();
            //for (uint a = 0; a < components.Count(); a++)
            //    Add(*components(a));
        }
        void Scene3D::Remove(const IRenderable3D<Vertex::Standard>& entity)
        {
            if (entity.Indices().IsEmpty())
                Buffers[entity.Topology()].Remove(entity);
            else
                IndexedBuffers[entity.Topology()].Remove(entity);
        }
        void Scene3D::Remove(const IRenderable2D<float>& entity)
        {
            PathBuffer.erase(&entity);
        }
        //void Scene3D::Render(GPU* gpu) const
        //{
        //    if (PathBuffer.size())
        //    {
        //        glStencilMask(~0);
        //        glEnable(GL_STENCIL_TEST);
        //        glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
        //        glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);

        //        for (const auto* p : PathBuffer)
        //            p->Render(gpu);

        //        glDisable(GL_STENCIL_TEST);
        //    }
        //}
        void Scene3D::Update()
        {
            for (uint a = 0; a < Stages3D.Count(); a++)
                delete Stages3D(a);

            Stages3D.Clear();

            for (auto& kvp : Buffers)
            {
                kvp.second.Update();
                Stages3D.Append(new RenderStage3D(kvp.first, &kvp.second, nullptr));
            }
            for (auto& kvp : IndexedBuffers)
            {
                kvp.second.Update();
                Stages3D.Append(new IndexedRenderStage3D(kvp.first, &kvp.second, nullptr));
            }
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