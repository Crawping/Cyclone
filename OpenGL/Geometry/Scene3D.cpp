#include "RenderStage3D.h"
#include "Collections/List.h"
#include "Interfaces/IRenderable.h"
#include "Geometry/Scene3D.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {





        const List<IRenderStage*>& Scene3D::Stages() const
        {
            return Stages3D;
        }



        /** CONSTRUCTOR **/
        Scene3D::Scene3D() : 
            _isVisible(true)
        {

        }
        Scene3D::~Scene3D()
        {
            //for (uint a = 0; a < Stages3D.Count(); a++)
            //    delete Stages3D(a);

            //for (auto& kvp : Buffers)
            //    delete kvp.second;

            //for (auto& kvp : IndexedBuffers)
            //    delete kvp.second;

            for (auto& kvp : RenderStages)
                delete kvp.second;
        }




        /** PUBLIC UTILITIES **/
        void Scene3D::Add(const IGeometric3D<Vertex::Standard>& entity)
        {
            const auto& vertices = entity.Points();
            const auto& indices = entity.Indices();

            if (indices.IsEmpty())
                Commands.Append(DrawCommand(vertices.Count(), 1, 0, Vertices.Count(), Commands.Count()));
            else
            {
                IndexedCommands.Append(IndexedDrawCommand(indices.Count(), 1, Indices.Count(), Vertices.Count(), IndexedCommands.Count()));
                for (uint a = 0; a < indices.Count(); a++)
                    Indices.Add(indices(a));
            }
            
            for (uint a = 0; a < vertices.Count(); a++)
                Vertices.Add(vertices(a));

            TransformData transforms = 
            {
                entity.ModelTransform().ToMatrix4x4(),
                Matrix4x4::Identity,
                entity.WorldTransform().ToMatrix4x4(),
            };

            TransformBuffer.Add(transforms);
        }

        void Scene3D::Add(const IMaterialEntity& entity)
        {
            MaterialData material =
            {
                entity.PrimaryColor(),
                entity.SecondaryColor(),
            };

            MaterialBuffer.Add(material);
        }

        void Scene3D::Add(const IRenderable3D<Vertex::Standard>& entity)
        {
            if (EntityIndices.count(&entity)) { return; }

            bool isIndexed = !entity.Indices().IsEmpty();

            EntityIndices[&entity] =
            {
                isIndexed ? IndexedCommands.Count() : Commands.Count(),
                EntityBuffer.Count(),
            };

            EntityData data =
            {
                MaterialBuffer.Count(),
                TransformBuffer.Count(),
            };

            EntityBuffer.Add(data);

            Add( (const IGeometric3D<Vertex::Standard>&)entity );
            Add( (const IMaterialEntity&)entity );
        }
        void Scene3D::Remove(const IRenderable3D<Vertex::Standard>& entity)
        {

        }
        void Scene3D::Update()
        {
            Indices.Update();
            Vertices.Update();
            EntityBuffer.Update();
            MaterialBuffer.Update();
            TransformBuffer.Update();

            for (auto& kvp : RenderStages)
                kvp.second->ClearCommands();

            for (auto& kvp : EntityIndices)
            {
                VertexTopologies topology = kvp.first->Topology();
                if (!RenderStages.count(topology))
                {
                    RenderStage3D* stage = new RenderStage3D(topology);
                    stage->
                         EntityBuffer(EntityBuffer)
                        .IndexData(Indices)
                        .MaterialBuffer(MaterialBuffer)
                        .TransformBuffer(TransformBuffer)
                        .VertexData(Vertices)
                        .Settings(_settings);

                    RenderStages[topology] = stage;
                }

                BufferIndices ids = kvp.second;
                if (kvp.first->Indices().IsEmpty())
                    RenderStages[topology]->Add(Commands(ids.CommandIndex));
                else
                    RenderStages[topology]->Add(IndexedCommands(ids.CommandIndex));
            }

            Stages3D.Clear();
            for (auto& kvp : RenderStages)
            {
                kvp.second->Update();
                Stages3D.Append(kvp.second);
            }

        }

        void Scene3D::Update(const IRenderable3D<Vertex::Standard>& entity)
        {
         
        }

    }
}