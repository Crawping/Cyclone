#include "RenderStage3D.h"
#include "Collections/List.h"
#include "Interfaces/IRenderable.h"
#include "Geometry/Scene3D.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {





        const List<IRenderStage*>& Scene3D::Stages() const
        {
            return Stages3D;
        }



        /** CONSTRUCTOR **/
        Scene3D::Scene3D() : 
            _isVisible(true)
        {

        }
        Scene3D::~Scene3D()
        {
            //for (uint a = 0; a < Stages3D.Count(); a++)
            //    delete Stages3D(a);
            for (auto& kvp : Buffers)
                delete kvp.second;

            for (auto& kvp : IndexedBuffers)
                delete kvp.second;
        }




        /** PUBLIC UTILITIES **/
        void Scene3D::Add(const IRenderable3D<Vertex::Standard>& entity)
        {

            VertexTopologies topology = entity.Topology();

            if (entity.Indices().IsEmpty())
            {
                if (!Buffers.count(topology))
                    //Buffers.emplace(topology, RenderStage3D<DrawCommand>(topology, _settings));
                    Buffers[topology] = new RenderStage3D<DrawCommand>(topology, _settings);

                Buffers[topology]->Add(entity);
            }
            else
            {
                if (!IndexedBuffers.count(topology))
                    //IndexedBuffers.emplace(topology, RenderStage3D<IndexedDrawCommand>(topology, _settings));
                    IndexedBuffers[topology] = new RenderStage3D<IndexedDrawCommand>(topology, _settings);

                IndexedBuffers[topology]->Add(entity);
            }


            //if (entity.Indices().IsEmpty())
            //    Buffers[entity.Topology()].Add(entity);
            //else
            //    IndexedBuffers[entity.Topology()].Add(entity);
        }
        void Scene3D::Remove(const IRenderable3D<Vertex::Standard>& entity)
        {
            //if (entity.Indices().IsEmpty())
            //    Buffers[entity.Topology()].Remove(entity);
            //else
            //    IndexedBuffers[entity.Topology()].Remove(entity);
        }
        void Scene3D::Update()
        {
            //for (uint a = 0; a < Stages3D.Count(); a++)
            //    delete Stages3D(a);

            //Stages3D.Clear();

            //for (auto& kvp : Buffers)
            //{
            //    kvp.second.Update();
            //    Stages3D.Append(new RenderStage3D(kvp.first, &kvp.second, _settings));
            //}
            //for (auto& kvp : IndexedBuffers)
            //{
            //    kvp.second.Update();
            //    Stages3D.Append(new IndexedRenderStage3D(kvp.first, &kvp.second, _settings));
            //}

            Stages3D.Clear();

            for (auto& kvp : Buffers)
            {
                kvp.second->Update();
                Stages3D.Append(kvp.second);
            }

            for (auto& kvp : IndexedBuffers)
            {
                kvp.second->Update();
                Stages3D.Append(kvp.second);
            }
        }

        void Scene3D::Update(const IRenderable3D<Vertex::Standard>& entity)
        {
            //if (entity.Indices().IsEmpty())
            //    Buffers[entity.Topology()].Update(entity);
            //else
            //    IndexedBuffers[entity.Topology()].Update(entity);
        }

    }
}