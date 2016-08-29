#include "Geometry/GeometryCollection.h"
#include "Interfaces/IRenderable.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** CONSTRUCTOR **/
        GeometryCollection::GeometryCollection() : 
            _needsUpdate(false)
        {

        }



        /** PUBLIC UTILITIES **/
        void GeometryCollection::Add(const IRenderableEntity& entity)
        {
            Buffers[entity.Topology()].Add(entity);
        }
        void GeometryCollection::Clear()
        {
            for (auto& kvp : Buffers)
                kvp.second.Clear();
        }
        void GeometryCollection::Remove(const IRenderableEntity& entity)
        {
            Buffers[entity.Topology()].Remove(entity);
        }
        void GeometryCollection::Update()
        {
            for (auto& kvp : Buffers)
                kvp.second.Update();
        }



        /** BINDING UTILITIES **/
        void GeometryCollection::Bind(VertexTopologies topology) const
        {
            if (!Buffers.count(topology)) { return; }
            Buffers.at(topology).Bind();
        }
        //void GeometryBuffer::Bind(int slot)             const
        //{

        //}
        //void GeometryBuffer::BindEntity(int slot)       const
        //{

        //}
        //void GeometryBuffer::BindResources()            const
        //{

        //}

        //void GeometryBuffer::Unbind()                   const
        //{

        //}
        //void GeometryBuffer::UnbindEntity()             const
        //{

        //}
        //void GeometryBuffer::UnbindResources()          const
        //{

        //}

    }
}