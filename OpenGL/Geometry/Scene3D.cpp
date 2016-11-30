#include "RenderStage3D.h"
#include "Collections/List.h"
#include "Interfaces/IRenderable.h"
#include "Geometry/Scene3D.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {

        List<IRenderStage*> Scene3D::Stages() const
        {
            List<IRenderStage*> stages;
            for (auto& kvp : RenderStages)
                stages.Append(kvp.second);

            for (auto& kvp : IndexedStages)
                stages.Append(kvp.second);

            return stages;
        }



        /** CONSTRUCTOR **/
        Scene3D::Scene3D() : 
            _isVisible(true)
        {

        }
        Scene3D::~Scene3D()
        {
            for (auto& kvp : RenderStages)
                delete kvp.second;

            for (auto& kvp : IndexedStages)
                delete kvp.second;
        }

        

        /** PUBLIC UTILITIES **/
        void Scene3D::Add(const IRenderable3D<Vertex::Standard>& entity)
        {
            if (EntityIndices.count(&entity)) { return; }

            uint idxEntities    = Entities.Count();
            uint nIndices       = entity.Indices().Count();
            uint idxIndices     = Indices.Count();
            uint nVertices      = entity.Points().Count();
            uint idxVertices    = Vertices.Count();

            BufferIndices ids =
            {
                idxEntities,
                nIndices,
                idxIndices,
                Add( (const IMaterialEntity&)entity ),
                Add( (const IGeometric3D<Vertex::Standard>&)entity ),
                nVertices,
                idxVertices,
            };
            EntityIndices[&entity] = ids;

            EntityData data =
            {
                ids.MaterialIndex.Index(),
                ids.TransformIndex.Index(),
            };
            Entities.Add(data);
        }
        void Scene3D::Remove(const IRenderable3D<Vertex::Standard>& entity)
        {
            
        }
        void Scene3D::Update()
        {
            Indices.Update();
            Vertices.Update();
            Entities.Update();
            Materials.Update();
            Transforms.Update();

            for (auto& kvp : RenderStages)
                kvp.second->ClearCommands();

            uint idx = 0;
            for (auto& kvp : EntityIndices)
            {
                VertexTopologies topology = kvp.first->Topology();
                bool isIndexed = !kvp.first->Indices().IsEmpty();
                BufferIndices ids = kvp.second;

                if (isIndexed)
                {
                    if (!IndexedStages.count(topology))
                        CreateStage(topology, isIndexed);

                    IndexedStages[topology]->Add(IndexedDrawCommand(ids.IndicesCount, 1, ids.IndicesIndex, ids.VertexIndex, ids.EntityIndex));
                }
                else
                {
                    if (!RenderStages.count(topology))
                        CreateStage(topology, isIndexed);

                    RenderStages[topology]->Add(DrawCommand(ids.VertexCount, 1, 0, ids.VertexIndex, ids.EntityIndex));
                }
            }

            for (auto& kvp : RenderStages)
                kvp.second->Update();
            for (auto& kvp : IndexedStages)
                kvp.second->Update();

        }
        void Scene3D::Update(const IRenderable3D<Vertex::Standard>& entity)
        {
            if (!EntityIndices.count(&entity)) { return; }

            TransformData transforms =
            {
                entity.ModelTransform().ToMatrix4x4(),
                Matrix4x4::Identity,
                entity.WorldTransform().ToMatrix4x4(),
            };
            
            MaterialData material =
            {
                entity.PrimaryColor(),
                entity.SecondaryColor(),
            };

            BufferIndices ids = EntityIndices[&entity];
            Transforms.Set(ids.TransformIndex, transforms);
            Materials.Set(ids.MaterialIndex, material);
        }



        /** PRIVATE UTILITIES **/
        RegistryKey<TransformData> Scene3D::Add(const IGeometric3D<Vertex::Standard>& entity)
        {
            const auto& vertices = entity.Points();
            const auto& indices = entity.Indices();

            for (uint a = 0; a < indices.Count(); a++)
                Indices.Add(indices(a));

            for (uint a = 0; a < vertices.Count(); a++)
                Vertices.Add(vertices(a));

            TransformData transforms =
            {
                entity.ModelTransform().ToMatrix4x4(),
                Matrix4x4::Identity,
                entity.WorldTransform().ToMatrix4x4(),
            };

            return Transforms.Register(transforms);
        }
        RegistryKey<MaterialData> Scene3D::Add(const IMaterialEntity& entity)
        {
            MaterialData material =
            {
                entity.PrimaryColor(),
                entity.SecondaryColor(),
            };

            return Materials.Register(material);
        }
        void Scene3D::CreateStage(VertexTopologies topology, bool isIndexed)
        {
            List<BufferBinding> bindings =
            {
                { Vertices,     0 },
                { Entities,     2 },
                { Materials,    3 },
                { Transforms,   4 },
            };

            RenderStage* stage = nullptr;
            if (isIndexed)
            {
                bindings.Insert(1, { Indices, 0 });
                stage = IndexedStages[topology] = new RenderStage3D<IndexedDrawCommand>();
            }
            else
                stage = RenderStages[topology] = new RenderStage3D<DrawCommand>();

            stage->
                 Settings(_settings)
                .Topology(topology)
                .Add(bindings);
        }

    }
}