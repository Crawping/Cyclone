#include "Collections/List.h"
#include "Interfaces/IMaterial.h"
#include "Interfaces/IRenderable.h"
#include "Pipelines/RenderStage3D.h"
#include "Scenes/Scene3D.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {

        List<IRenderStage&> Scene3D::Stages() const
        {
            List<IRenderStage&> stages;
            for (auto& kvp : RenderStages)
                stages.Append(*(kvp.second));

            for (auto& kvp : IndexedStages)
                stages.Append(*(kvp.second));

            for (auto& c : Components.Values())
                stages.Append(c.Stages());

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
            ResourceMapping ids =
            {
                Entities.Count(),
                geometry.Indices().Count(),
                Indices.Count(),
                Transforms.Count(),
                geometry.Points().Count(),
                Vertices.Count(),
            };

            Add(geometry);

            MaterialData material =
            {
                entity.Material().PrimaryColor(),
                entity.Material().SecondaryColor(),
            };

            TransformData transforms =
            {
                entity.ModelTransform().ToMatrix4x4(),
                entity.TextureTransform().ToMatrix4x4(),
                entity.WorldTransform().ToMatrix4x4(),
            };
            Transforms.Add(transforms);

            ids.MaterialKey = Materials.Register(material);
            EntityIndices[&entity] = ids;

            EntityData data =
            {
                ids.MaterialKey.Index(),
                ids.TransformIndex,
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
                ResourceMapping ids = kvp.second;

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

            for (auto& c : Components.Values())
                c.Update();

        }
        void Scene3D::Update(const IRenderable3D<Vector3>& entity)
        {
            if (!EntityIndices.count(&entity)) { return; }

            TransformData transforms =
            {
                entity.ModelTransform().ToMatrix4x4(),
                entity.TextureTransform().ToMatrix4x4(),
                entity.WorldTransform().ToMatrix4x4(),
            };
            
            MaterialData material =
            {
                entity.Material().PrimaryColor(),
                entity.Material().SecondaryColor(),
            };

            ResourceMapping ids = EntityIndices[&entity];
            Transforms.Set(ids.TransformIndex, transforms);

            ids.MaterialKey = Materials.Register(material);
            EntityIndices[&entity] = ids;
        }


        void Scene3D::Insert(const string& name, ISceneComponent& component)
        {
            Components.Insert(name, component);
        }
        void Scene3D::Associate(const string& name, const IRenderable3D<Vector3>& entity)
        {
            if (EntityIndices.count(&entity))   { return; }
            if (TempIndices.Contains(&entity))  { return; }
            if (!Components.Contains(name))     { return; }

            const auto& geometry = entity.Geometry();
            ResourceMapping ids =
            {
                Entities.Count(),
                geometry.Indices().Count(),
                Indices.Count(),
                Transforms.Count(),
                geometry.Points().Count(),
                Vertices.Count(),
                RegistryKey<MaterialData>(),
                geometry.Topology(),
            };
            
            Add(geometry);

            MaterialData material =
            {
                entity.Material().PrimaryColor(),
                entity.Material().SecondaryColor(),
            };

            TransformData transforms =
            {
                entity.ModelTransform().ToMatrix4x4(),
                entity.TextureTransform().ToMatrix4x4(),
                entity.WorldTransform().ToMatrix4x4(),
            };
            Transforms.Add(transforms);

            ids.MaterialKey = Materials.Register(material);
            
            //EntityIndices[&entity] = ids;
            TempIndices.Insert(&entity, ids);
            //TempIndices[&entity] = ids;

            EntityData data =
            {
                ids.MaterialKey.Index(),
                ids.TransformIndex,
            };
            Entities.Add(data);

            Components[name].Insert(TempIndices[&entity]);
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
        void Scene3D::CreateLayer(VertexTopologies topology)
        {

        }
    }
}