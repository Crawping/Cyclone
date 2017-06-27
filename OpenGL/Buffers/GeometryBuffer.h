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
        /// <summary> A class that combines a vertex and index buffer to serve as inputted geometry data on the GPU. </summary>
        /// <remarks> This base declaration is completely empty and must be specialized in order to function. </remarks>
        template<typename ... T> class GeometryBuffer { };

        /// <summary> A class that combines a vertex and index buffer to serve as inputted geometry data on the GPU. </summary>
        template<> class GeometryBuffer<Vertex>: 
            public virtual IGraphicsBuffer
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the number of points to be rendered by the buffer. </summary>
                uint Count()                const override { return Math::Max(IndexCount(), PointCount()); }
                /// <summary> Gets the numeric identifier for the buffer on the GPU. </summary>
                uint ID()                   const override { return _vertices.ID(); }
                /// <summary> Gets the number of vertex indices stored within the buffer. </summary>
                uint IndexCount()           const { return _indices.Count(); }
                /// <summary> Gets whether the buffer contains any indexed vertices. </summary>
                bool IsIndexed()            const { return !_indices.IsEmpty(); }
                /// <summary> Gets whether the buffer has updates that need to be transferred to the GPU. </summary>
                bool NeedsUpdate()          const override { return _needsUpdate; }
                /// <summary> Gets the number of vertices stored within the buffer. </summary>
                uint PointCount()           const { return _vertices.Count(); }



                /** CONSTRUCTOR **/
                /// <summary> Constructs an empty new geometry buffer that can be used to store 3D vertex data. </summary>
                GeometryBuffer():           _needsUpdate(false) { }



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
