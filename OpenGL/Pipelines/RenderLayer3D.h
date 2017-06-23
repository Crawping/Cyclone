/* CHANGELOG 
 * Written by Josh Grooms on 20170622
 */

#pragma once
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

                struct GeometryData 
                {
                    uint IndicesCount;
                    uint IndicesIndex;
                    uint VertexCount;
                    uint VertexIndex; 
                };

                IndexBuffer                         _indices;
                VertexBuffer<Vertex>                _vertices;

                BST<uint, GeometryData>             _data;
                BST<uint, Resource<IGeometric>>     _geometry;
                ArrayList<Resource<IGeometric>>     _geometryUpdates;


                OpenGLAPI bool Contains(const Resource<IGeometric>& geometry)   const;
                OpenGLAPI Vector<Vector2> GatherCounts()                        const;
                OpenGLAPI void UpdateGeometryData(const Resource<IGeometric>& geometry);


        };
    }
}
