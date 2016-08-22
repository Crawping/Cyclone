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
        void Scene3D::Bind(VertexTopologies topology) const
        {
            if (!Buffers.count(topology)) { return; }

            Buffers.at(topology).Bind();
        }
        uint Scene3D::PerTopologyCount(VertexTopologies topology) const
        {
            if (!Buffers.count(topology))
                return 0;
            
            return Buffers.at(topology).Count();
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
            
            for (auto topology : _topologies)
                Buffers[topology].Clear();

            _topologies.clear();

            for (auto* entity : EntitySet)
            {
                Buffers[entity->Topology()].Add(*entity);
                _topologies.insert(entity->Topology());
            }

            for (auto topology : _topologies)
            {
                Buffers[topology].Update();
            }

            NeedsUpdate = false;
        }

    }
}