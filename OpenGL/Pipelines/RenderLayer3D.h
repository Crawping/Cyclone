/* CHANGELOG 
 * Written by Josh Grooms on 20170622
 */

#pragma once
#include "Buffers/GeometryBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexBuffer.h"
#include "Pipelines/RenderLayer.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class RenderLayer3D: public RenderLayer
        {
            public:

                //template<typename T> using ResourceList = List< Resource<T> >;


                /** PROPERTIES **/
                //ResourceList<IRenderStage> Stages()                             const { return _stages.Values(); }



                /** CONSTRUCTOR **/
                RenderLayer3D() { }



                /** UTILITIES **/
                OpenGLAPI void Insert(const Resource<IRenderable>& entity)  override;
                OpenGLAPI void Insert(const Resource<IGeometric>& geometry);
                OpenGLAPI void Update()                                     override;
                OpenGLAPI void Update(const Resource<IGeometric>& geometry);

            private:

                struct BufferIndices 
                {
                    uint IndicesCount;
                    uint IndicesIndex;
                    uint VertexCount;
                    uint VertexIndex; 

                    bool operator ==(const BufferIndices& other) const
                    {
                        return 
                            (IndicesCount == other.IndicesCount)    &&
                            (IndicesIndex == other.IndicesIndex)    &&
                            (VertexCount == other.VertexCount)      &&
                            (VertexIndex == other.VertexIndex);
                    }
                };

                GeometryBuffer<Vertex>              _vertices;
                ArrayList<BufferIndices>            _keys;
                ArrayList<Resource<IGeometric>>     _geometry;
                Array<uint, 2>                      _invalidRange;
                BST<uint, uint>                     _mapping;


                OpenGLAPI bool Contains(const Resource<IGeometric>& geometry)   const;
                OpenGLAPI void Invalidate(uint geometry);
                OpenGLAPI void InvalidateAll(uint geometry);
                OpenGLAPI Vector<Vector2> UpdateCounts()                        const;
                OpenGLAPI void UpdateGeometryData(const Resource<IGeometric>& geometry);

        };
    }
}
