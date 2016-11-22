/* CHANGELOG
 * Written by Josh Grooms on 20161009
 */

#pragma once
#include "EnumerationsGL.h"
#include "GraphicsSettings.h"
#include "Buffers/DrawBuffer3D.h"
#include "Interfaces/IRenderStage.h"
#include <map>



namespace Cyclone
{
    namespace Utilities { struct ITransformation3D; }

    namespace OpenGL
    {
        class IGraphicsBuffer;
        class FrameBuffer;
        class GraphicsPipeline;

        struct RenderStage : public virtual IRenderStage
        {
            public:

                /** PROPERTIES **/
                //const IGraphicsBuffer* Data()                               const override { return _data; }
                const GraphicsSettings& Settings()                          const override { return _settings; }
                VertexTopologies Topology()                                 const override { return _topology; }

                OpenGLAPI RenderStage& IsBlendEnabled(bool value);
                OpenGLAPI RenderStage& IsDepthTestEnabled(bool value);
                OpenGLAPI RenderStage& IsStencilTestEnabled(bool value);
                OpenGLAPI RenderStage& CullingMode(CullingModes value);
                OpenGLAPI RenderStage& Pipeline(GraphicsPipeline* value);
                OpenGLAPI RenderStage& Projection(ITransformation3D* value);
                OpenGLAPI RenderStage& Settings(const GraphicsSettings& value);
                OpenGLAPI RenderStage& Target(FrameBuffer* value);
                OpenGLAPI RenderStage& Topology(VertexTopologies value);
                OpenGLAPI RenderStage& View(ITransformation3D* value);
                


                /** UTILITIES **/
                //OpenGLAPI void Render();

            protected:

                /** CONSTRUCTOR **/
                OpenGLAPI RenderStage(VertexTopologies topology = VertexTopologies::Triangles);
                OpenGLAPI RenderStage(VertexTopologies topology, const GraphicsSettings& settings);

            private:

                //const IGraphicsBuffer*  _data;
                GraphicsSettings        _settings;
                VertexTopologies        _topology;

        };

        //template<typename T>
        struct RenderStage3D : public RenderStage
        {
            public:

                /** PROPERTIES **/
                const IGraphicsBuffer* Data()                               const override { return nullptr; }

                OpenGLAPI RenderStage3D& EntityData(const UniformBuffer<PerEntity>& entities);
                OpenGLAPI RenderStage3D& IndexData(const IndexBuffer& indices);
                OpenGLAPI RenderStage3D& VertexData(const VertexBuffer<Vertex::Standard>& vertices);


                /** CONSTRUCTORS **/
                RenderStage3D(VertexTopologies topology) : 
                    RenderStage(topology)
                { 
                
                }
                RenderStage3D(VertexTopologies topology, const GraphicsSettings& settings) :
                    RenderStage(topology, settings)
                {

                }



                /** UTILITIES **/
                //OpenGLAPI void Add(const IRenderable3D<Vertex::Standard>& entity);
                OpenGLAPI void Add(const DrawCommand& command);
                OpenGLAPI void Add(const IndexedDrawCommand& command);

                OpenGLAPI void Render();
                OpenGLAPI void Update();


            private:

                //DrawBuffer3D<T, PerEntity, Vertex::Standard>       _data;
                CommandBuffer<DrawCommand>                          Commands;
                CommandBuffer<IndexedDrawCommand>                   IndexedCommands;

                const UniformBuffer<PerEntity>*                     Entities;
                const IndexBuffer*                                  Indices;
                const VertexBuffer<Vertex::Standard>*               Vertices;


                std::map<const IRenderable3D<Vertex::Standard>*, uint>      EntityIndices;
                std::set<const IRenderable3D<Vertex::Standard>*>            ToUpdate;

        };




        //struct IndexedRenderStage3D : public RenderStage3D
        //{
        //    public:

        //        IndexedRenderStage3D(VertexTopologies topology, const IGraphicsBuffer* data) : 
        //            RenderStage3D(topology, data)
        //        {

        //        }
        //        IndexedRenderStage3D(VertexTopologies topology, const IGraphicsBuffer* data, const GraphicsSettings& settings) : 
        //            RenderStage3D(topology, data, settings)
        //        {

        //        }

        //        OpenGLAPI void Render() override;

        //};

    }
}
