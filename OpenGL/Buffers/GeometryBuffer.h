/* CHANGELOG
 * Written by Josh Grooms on 20170625
 */

#pragma once
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexBuffer.h"



namespace Cyclone
{
    namespace OpenGL
    {
        template<typename ... T> class GeometryBuffer { };

        template<> class GeometryBuffer<Vertex>: 
            public virtual IGraphicsBuffer
        {
            public:

                /** PROPERTIES **/
                uint Count()                const override { return Math::Max(IndexCount(), PointCount()); }
                uint ID()                   const override { return _vertices.ID(); }
                uint IndexCount()           const { return _indices.Count(); }
                bool IsIndexed()            const { return !_indices.IsEmpty(); }
                bool NeedsUpdate()          const override { return _needsUpdate; }
                uint PointCount()           const { return _vertices.Count(); }



                /** CONSTRUCTOR **/
                GeometryBuffer():
                    _needsUpdate(false)
                {

                }



                /** UTILITIES **/
                void Append(const Vertex& vertex)                           { _vertices.Append(vertex); }
                void Append(const ICollection<Vertex>& vertices)            { _vertices.Append(vertices); }
                void Append(uint index)                                     { _indices.Append(index); }
                void Append(const ICollection<uint>& indices)               { _indices.Append(indices); }
                void Clear()                                                override
                {
                    _vertices.Clear();
                    _indices.Clear();
                }
                void Set(uint index, const ICollection<Vertex>& vertices)   { _vertices.Set(index, vertices); }
                void Set(uint index, const ICollection<uint>& indices)      { _indices.Set(index, indices); }
                void Update()                                               override
                {
                    _indices.Update();
                    _vertices.Update();
                }



                /** BINDING UTILITIES **/
                void Bind(int slot = 0)                             const override
                {
                    BindEntity(slot);
                    BindResources();
                }
                void BindEntity(int slot = 0)                       const override
                {
                    _vertices.Bind(slot);
                    if (IsIndexed()) { _indices.Bind(slot); }
                }
                void BindResources()                                const override { }
                void Unbind()                                       const override
                {
                    UnbindResources();
                    UnbindEntity();
                }
                void UnbindEntity()                                 const override
                {
                    if (IsIndexed()) { _indices.Unbind(); }
                    _vertices.Unbind();
                }
                void UnbindResources()                              const override { }

            private:

                IndexBuffer             _indices;
                bool                    _needsUpdate;
                VertexBuffer<Vertex>    _vertices;

        };
    }
}
