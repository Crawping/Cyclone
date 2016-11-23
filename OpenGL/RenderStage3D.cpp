#include "RenderStage3D.h"
#include "Buffers/GraphicsBuffer.h"
#include "Interfaces/ITransformation3D.h"



namespace Cyclone
{
    namespace OpenGL
    {
        
        /** PROPERTIES **/
        RenderStage& RenderStage::IsBlendEnabled(bool value) 
        { 
            _settings.IsBlendEnabled = value; 
            return *this;
        }
        RenderStage& RenderStage::IsDepthTestEnabled(bool value) 
        { 
            _settings.IsDepthTestEnabled = value; 
            return *this;
        }
        RenderStage& RenderStage::IsStencilTestEnabled(bool value)
        { 
            _settings.IsStencilTestEnabled = value; 
            return *this;
        }
        RenderStage& RenderStage::CullingMode(CullingModes value)
        {
            _settings.CullingMode = value;
            return *this;
        }
        RenderStage& RenderStage::Pipeline(GraphicsPipeline* value)
        { 
            _settings.Pipeline = value;
            return *this;
        }
        RenderStage& RenderStage::Projection(ITransformation3D* value) 
        { 
            _settings.Projection = value;
            return *this;
        }
        RenderStage& RenderStage::Settings(const GraphicsSettings& value)
        {
            return this->
                 IsBlendEnabled(value.IsBlendEnabled)
                .IsDepthTestEnabled(value.IsDepthTestEnabled)
                .IsStencilTestEnabled(value.IsStencilTestEnabled)
                .CullingMode(value.CullingMode)
                .Pipeline(value.Pipeline)
                .Projection(value.Projection)
                .Target(value.Target)
                .View(value.View);
        }
        RenderStage& RenderStage::Target(FrameBuffer* value)
        { 
            _settings.Target = value; 
            return *this;
        }
        RenderStage& RenderStage::Topology(VertexTopologies value)
        {
            _topology = value;
            return *this;
        }
        RenderStage& RenderStage::View(ITransformation3D* value) 
        { 
            _settings.View = value;
            return *this;
        }



        /** CONSTRUCTORS **/
        RenderStage::RenderStage(VertexTopologies topology) :
            _topology(topology)
        {

        }
        RenderStage::RenderStage(VertexTopologies topology, const GraphicsSettings& settings) :
            _settings(settings),
            _topology(topology)
        {

        }






        //RenderStage3D& RenderStage3D::EntityData(const UniformBuffer<PerEntity>& entities)
        //{
        //    Entities = &entities;
        //    return *this;
        //}
        RenderStage3D& RenderStage3D::IndexData(const IndexBuffer& indices)
        {
            Indices = &indices;
            return *this;
        }
        RenderStage3D& RenderStage3D::VertexData(const VertexBuffer<Vertex::Standard>& vertices)
        {
            Vertices = &vertices;
            return *this;
        }

        RenderStage3D& RenderStage3D::EntityBuffer(const UniformBuffer<EntityData>& value)
        {
            _entityBuffer = &value;
            return *this;
        }
        RenderStage3D& RenderStage3D::MaterialBuffer(const UniformBuffer<MaterialData>& value)
        {
            _materialBuffer = &value;
            return *this;
        }
        RenderStage3D& RenderStage3D::TransformBuffer(const UniformBuffer<TransformData>& value)
        {
            _transformBuffer = &value;
            return *this;
        }




        void RenderStage3D::Add(const DrawCommand& command)
        {
            Commands.Add(command);
        }
        void RenderStage3D::Add(const IndexedDrawCommand& command)
        {
            IndexedCommands.Add(command);
        }
        void RenderStage3D::ClearCommands()
        {
            Commands.Clear();
            IndexedCommands.Clear();
        }


        void RenderStage3D::Render()
        {
            //Entities->Bind();
            Indices->Bind();
            Vertices->Bind();
            _entityBuffer->Bind(2);
            _materialBuffer->Bind(3);
            _transformBuffer->Bind(4);
            
            if (!Commands.IsEmpty())
            {
                Commands.Bind();
                glMultiDrawArraysIndirect(Topology(), 0, Commands.Count(), 0);
            }

            if (!IndexedCommands.IsEmpty())
            {
                IndexedCommands.Bind();
                glMultiDrawElementsIndirect(Topology(), NumericFormats::UInt, 0, IndexedCommands.Count(), 0);
            }
        }

        void RenderStage3D::Update()
        {
            Commands.Update();
            IndexedCommands.Update();
        }

    }
}