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






        RenderStage3D& RenderStage3D::EntityData(const UniformBuffer<PerEntity>& entities)
        {
            Entities = &entities;
            return *this;
        }
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

        void RenderStage3D::Add(const DrawCommand& command)
        {
            Commands.Add(command);
        }
        void RenderStage3D::Add(const IndexedDrawCommand& command)
        {
            IndexedCommands.Add(command);
        }



        //template<typename T>
        //void RenderStage3D<T>::Add(const IRenderable3D<Vertex::Standard>& entity)
        //{
        //    if (EntityIndices.count(&entity)) { return; }
        //    EntityIndices[&entity] = _data.CommandCount();

        //    uint nvertices = entity.Indices().IsEmpty() ? entity.Points().Count() : entity.Indices().Count();
        //    T cmd(nvertices, 1, _data.IndexCount(), _data.VertexCount(), _data.CommandCount());

        //    PerEntity ent = { entity.WorldTransform().ToMatrix4x4(), entity.PrimaryColor() };

        //    _data.Add(cmd, ent, entity.Points(), entity.Indices());
        //}

        //template<typename T>
        void RenderStage3D::Render()
        {
            Entities->Bind();
            Indices->Bind();
            Vertices->Bind();
            
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

            //if (_data.IndexCount())
            //    glMultiDrawElementsIndirect(Topology(), NumericFormats::UInt, 0, _data.CommandCount(), 0);
            //else
            //    glMultiDrawArraysIndirect(Topology(), 0, _data.CommandCount(), 0);
        }

        template<typename T>
        void RenderStage3D<T>::Update()
        {
            //_data.Update();
            Commands.Update();
            IndexedCommands.Update();
        }




        //template class RenderStage3D<DrawCommand>;
        //template class RenderStage3D<IndexedDrawCommand>;

    }
}