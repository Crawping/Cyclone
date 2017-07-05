/* CHANGELOG 
 * Written by Josh Grooms on 20170622
 */

#pragma once
#include "Buffers/GeometryBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexBuffer.h"
#include "Resources/RenderLayer.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class RenderLayer3D: public RenderLayer
        {
            public:

                struct GeometryData;
                //template<typename T> using ResourceList = List< Resource<T> >;


                /** PROPERTIES **/
                //ResourceList<IRenderStage> Stages()                             const { return _stages.Values(); }
                List<BufferBinding> Buffers() const override
                {
                    auto buffers = RenderLayer::Buffers();
                    buffers.Prepend({ _vertices, 0 });
                    return buffers;
                }



                /** CONSTRUCTOR **/
                RenderLayer3D() { }



                /** UTILITIES **/
                using RenderLayer::IndexOf;
                using RenderLayer::Insert;
                using RenderLayer::Update;

                //uint IndexOf(const Resource<IRenderable>& entity) const override { return RenderLayer::IndexOf(entity); }
                OpenGLAPI const GeometryData& IndexOf(const Resource<IGeometric>& geometry) const;
                OpenGLAPI void Insert(const Resource<IRenderable>& entity)  override;
                OpenGLAPI void Insert(const Resource<IGeometric>& geometry);
                OpenGLAPI void Update()                                     override;
                OpenGLAPI void Update(const Resource<IGeometric>& geometry);

            private:

                struct GeometryData 
                {
                    uint IndicesCount;
                    uint IndicesIndex;
                    uint VertexCount;
                    uint VertexIndex; 

                    bool operator ==(const GeometryData& other) const
                    {
                        return 
                            (IndicesCount == other.IndicesCount)    &&
                            (IndicesIndex == other.IndicesIndex)    &&
                            (VertexCount == other.VertexCount)      &&
                            (VertexIndex == other.VertexIndex);
                    }
                };


                GeometryBuffer<Vertex>              _vertices;
                ArrayList<GeometryData>             _mapping;
                BST<uint, Resource<IGeometric>>     _geometry;
                Array<uint, 2>                      _updateRange;


                OpenGLAPI bool Contains(const Resource<IGeometric>& geometry)   const;
                OpenGLAPI void Invalidate(const Resource<IGeometric>& geometry);
                OpenGLAPI void Invalidate(uint index);
                OpenGLAPI void Invalidate(uint idxA, uint idxB);
                OpenGLAPI Vector<Vector2> UpdateCounts()                        const;
                OpenGLAPI void UpdateGeometryData(uint index);

        };
    }
}
