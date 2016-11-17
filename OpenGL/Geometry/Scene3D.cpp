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
        void Scene3D::Remove(const IRenderable3D<Vertex::Standard>& entity)
        {
            if (entity.Indices().IsEmpty())
                Buffers[entity.Topology()].Remove(entity);
            else
                IndexedBuffers[entity.Topology()].Remove(entity);
        }
        void Scene3D::Update()
        {
            for (uint a = 0; a < Stages3D.Count(); a++)
                delete Stages3D(a);

            Stages3D.Clear();

            for (auto& kvp : Buffers)
            {
                kvp.second.Update();
                Stages3D.Append(new RenderStage3D(kvp.first, &kvp.second, _settings));
            }
            for (auto& kvp : IndexedBuffers)
            {
                kvp.second.Update();
                Stages3D.Append(new IndexedRenderStage3D(kvp.first, &kvp.second, _settings));
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