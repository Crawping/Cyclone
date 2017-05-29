#include "Interfaces/IRenderable.h"
#include "Interfaces/IGeometric.h"
#include "Interfaces/IModel.h"
#include "Interfaces/ISpatialTransform.h"
#include "Libraries/Material3D.h"
#include "Pipelines/RenderStage3D.h"
#include "Scenes/SceneLayer3D.h"
#include "Scenes/Scene3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/
        List<BufferBinding> SceneLayer3D::Buffers() const
        {
            return
            {
                { Vertices,     0 },
                { Indices,      0 },
                { Entities,     2 },
                { Materials,    3 },
                { Transforms,   4 },
            };
        }
        List<ISceneComponent&> SceneLayer3D::Components() const
        {
            List<ISceneComponent&> components;
            components.Append((ISceneComponent&)*this);

            for (auto* component : _components.Values())
                components.Append(*component);

            return components;
        }
        List<IRenderStage&> SceneLayer3D::Stages() const
        {
            List<IRenderStage&> stages = SceneComponent3D::Stages();

            for (auto* stage : _components.Values())
                stages.Append(stage->Stages());

            if (!stages.IsEmpty())
            {
                stages.First().ClearBuffers();
                stages.First().Add(Buffers());
            }

            return stages;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        SceneLayer3D::SceneLayer3D(const string& name, ISceneLayer& parent) : 
            SceneComponent3D(name, parent)
        {

        }



        /** UTILITIES **/
        void SceneLayer3D::Insert(const string& name, ISceneComponent& stage)
        {
            _components.Insert(name, &stage);
        }
        void SceneLayer3D::Remove(const string& name)
        {
            _components.Remove(name);
        }
        void SceneLayer3D::Update()
        {
            SceneComponent3D::Update();

            Indices.Update();
            Vertices.Update();
            Entities.Update();
            Materials.Update();
            Transforms.Update();

            for (auto& c : _components.Values())
                c->Update();
        }
        void SceneLayer3D::Update(const IRenderable& entity)
        {
            if (!Mappings.Contains(&entity)) { return; }

            ResourceMapping& map = Mappings[&entity];
            Register(map, entity.Material());
            //Register(map, entity.Transforms());
            Register(map, entity);
        }



        /** PROTECTED UTILITIES **/
        ResourceMapping& SceneLayer3D::Register(const IRenderable& entity)
        {
            if (Mappings.Contains(&entity)) { return Mappings[&entity]; }

            Mappings.Insert(&entity, ResourceMapping());
            ResourceMapping& map = Mappings[&entity];

            Register(map, entity.Model().Geometry());
            Register(map, entity.Material());
            //Register(map, entity.Transforms());
            Register(map, entity);

            return map;
        }
        void SceneLayer3D::Remove(const IRenderable& entity)
        {
            if (!Mappings.Contains(&entity)) { return; }

            ResourceMapping& map = Mappings[&entity];
            Entities.Remove(map.EntityKey);
            Materials.Remove(map.MaterialKey);
            Transforms.Remove(map.TransformKey);

            Mappings.Remove(&entity);
        }



        /** PRIVATE UTILITIES **/
        void SceneLayer3D::Register(ResourceMapping& map, const IGeometric& entity)
        {
            const auto& indices = entity.Indices();
            const auto& mapping = entity.Mapping();
            const auto& normals = entity.Normals();
            const auto& points = entity.Points();

            map.IndicesCount = indices.Count();
            map.IndicesIndex = Indices.Count();
            map.Topology = entity.Topology();
            map.VertexCount = points.Count();
            map.VertexIndex = Vertices.Count();

            for (uint a = 0; a < indices.Count(); a++)
                Indices.Add(indices(a));

            for (uint a = 0; a < points.Count(); a++)
                Vertices.Add(Vertex(points(a), normals(a), (Vector2)mapping(a)));
        }
        void SceneLayer3D::Register(ResourceMapping& map, const IMaterial& material)
        {
            if (map.MaterialKey.IsValid())
                Materials.Set(map.MaterialKey, material.Data());
            else
                map.MaterialKey = Materials.Register(material.Data());
        }
        void SceneLayer3D::Register(ResourceMapping& map, const IRenderable& entity)
        {
            TransformData tdata =
            {
                Matrix4x4::Identity,
                Matrix4x4::Identity,
                entity.Model().Transform().ToMatrix4x4()
            };

            if (map.TransformKey.IsValid())
                Transforms.Set(map.TransformKey, tdata);
            else
                map.TransformKey = Transforms.Register(tdata);

            EntityData data =
            {
                (uint)map.MaterialKey.Index(),
                (uint)map.TransformKey.Index(),
            };


            if (map.EntityKey.IsValid())
                Entities.Set(map.EntityKey, data);
            else
                map.EntityKey = Entities.Register(data);
        }

    }
}