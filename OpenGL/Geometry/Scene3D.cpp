#include "RenderStage3D.h"
#include "Collections/List.h"
#include "Interfaces/IMaterial.h"
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
        void Scene3D::Add(const IRenderable3D<Vector3>& entity)
        {
            if (EntityIndices.count(&entity)) { return; }

            const auto& geometry = entity.Geometry();

            uint idxEntities    = Entities.Count();
            uint nIndices       = geometry.Indices().Count();
            uint idxIndices     = Indices.Count();
            uint nVertices      = geometry.Points().Count();
            uint idxVertices    = Vertices.Count();

            Add(geometry);

            TransformData transforms =
            {
                entity.ModelTransform().ToMatrix4x4(),
                Matrix4x4::Identity,
                entity.WorldTransform().ToMatrix4x4(),
            };

            BufferIndices ids =
            {
                idxEntities,
                nIndices,
                idxIndices,
                Add( entity.Material() ),
                Transforms.Register(transforms),
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
        void Scene3D::Remove(const IRenderable3D<Vector3>& entity)
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
                VertexTopologies topology = kvp.first->Geometry().Topology();
                BufferIndices ids = kvp.second;

                if (ids.IndicesCount)
                {
                    if (!IndexedStages.count(topology))
                        CreateStage(topology, true);

                    IndexedStages[topology]->Add(IndexedDrawCommand(ids.IndicesCount, 1, ids.IndicesIndex, ids.VertexIndex, ids.EntityIndex));
                }
                else
                {
                    if (!RenderStages.count(topology))
                        CreateStage(topology, false);

                    RenderStages[topology]->Add(DrawCommand(ids.VertexCount, 1, 0, ids.VertexIndex, ids.EntityIndex));
                }
            }

            for (auto& kvp : RenderStages)
                kvp.second->Update();
            for (auto& kvp : IndexedStages)
                kvp.second->Update();

        }
        void Scene3D::Update(const IRenderable3D<Vector3>& entity)
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
                entity.Material().PrimaryColor(),
                entity.Material().SecondaryColor(),
            };

            BufferIndices ids = EntityIndices[&entity];
            Transforms.Set(ids.TransformIndex, transforms);
            Materials.Set(ids.MaterialIndex, material);
        }



        /** PRIVATE UTILITIES **/
        void Scene3D::Add(const IGeometric<Vector3>& entity)
        {
            const auto& indices = entity.Indices();
            const auto& mapping = entity.Mapping();
            const auto& normals = entity.Normals();
            const auto& vertices = entity.Points();

            for (uint a = 0; a < indices.Count(); a++)
                Indices.Add(indices(a));

            for (uint a = 0; a < vertices.Count(); a++)
                Vertices.Add(Vertex::Standard(vertices(a), normals(a), (Vector2)mapping(a)));
        }
        RegistryKey<MaterialData> Scene3D::Add(const IMaterial& material)
        {
            MaterialData mat =
            {
                material.PrimaryColor(),
                material.SecondaryColor(),
            };

            return Materials.Register(mat);
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