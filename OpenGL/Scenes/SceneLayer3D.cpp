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

        /** INTERNAL CLASSES **/
        struct StageGroup3D
        {
            RenderStage3D<IndexedDrawCommand>   Indexed;
            RenderStage3D<DrawCommand>          NonIndexed;
        };



        /** PROPERTIES **/
        List<BufferBinding> SceneLayer3D::Buffers() const
        {
            return _resources.Buffers();
            //auto buffers = SceneComponent3D::Buffers();
            //buffers.Append({ _materials,    3 });
            //buffers.Append({ _transforms,   4 });
            //return buffers;
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
            //List<IRenderStage&> stages = SceneComponent3D::Stages();
            List<IRenderStage&> stages;

            for (auto* cmp : _components.Values())
                stages.Append(cmp->Stages());

            for (auto& stage : _staging)
            {
                stages.Append(stage.Value->Indexed);
                stages.Append(stage.Value->NonIndexed);
            }

            if (!stages.IsEmpty())
            {
                stages.First().ClearBuffers();
                stages.First().Append(Buffers());
            }

            return stages;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        SceneLayer3D::SceneLayer3D(const string& name, ISceneLayer& parent): 
            SceneComponent3D(name, parent)
        {

        }
        SceneLayer3D::~SceneLayer3D()
        {
            for (auto& stage : _staging)
                delete(stage.Value);
        }



        /** UTILITIES **/
        //uint SceneLayer3D::IndexOf(const Resource<IMaterial>& material) const
        //{
        //    return _resources.IndexOf(material);
        //    //return _materials.IndexOf(material.ID());
        //}
        //uint SceneLayer3D::IndexOf(const Resource<IRenderable>& entity) const
        //{
        //    return _resources.IndexOf(entity);
        //    //return _entities.IndexOf(entity.ID());
        //}
        //auto SceneLayer3D::GeometryIndices(const Resource<IGeometric>& geometry) const
        //{
        //    //return _resources.IndexOf(geometry);
        //    return _resources.GeometryIndices(geometry);
        //}
        void SceneLayer3D::Insert(const string& name, ISceneComponent& stage)
        {
            _components.Insert(name, &stage);
        }
        void SceneLayer3D::Insert(const Resource<IRenderable>& entity)
        {
            //if (entity.IsNull() || _entities.Contains(entity.ID())) { return; }
            //_entities.Insert(entity.ID(), entity);
            _resources.Insert(entity);
            _entities.Insert(entity.ID(), entity);
            //SceneComponent3D::Insert(entity);
            //Update(entity);
        }
        void SceneLayer3D::Remove(const string& name)
        {
            _components.Remove(name);
        }
        void SceneLayer3D::Update()
        {
            for (auto& c : _components.Values())
                c->Update();

            _resources.Update();

            for (auto& kvp : _staging)
            {
                kvp.Value->Indexed.ClearCommands();
                kvp.Value->NonIndexed.ClearCommands();
            }

            for (const auto& e : _entities)
            {
                if (e.Value->Model().IsNull() || e.Value->Model()->Geometry().IsNull())
                    continue;

                const auto& geometry = e.Value->Model()->Geometry();
                auto topology = geometry->Topology();

                StageGroup3D* stage =
                    _staging.Contains(topology) ? _staging[topology] :
                    CreateStage(topology);

                const auto& indices = _resources.IndexOf(geometry);
                if (indices.IndicesCount)
                    stage->Indexed.Append
                    (
                        IndexedDrawCommand
                        (
                            indices.IndicesCount, 1, 
                            indices.IndicesIndex, 
                            indices.VertexIndex,
                            _resources.IndexOf(e.Value)
                        )
                    );
                else
                    stage->NonIndexed.Append
                    (
                        DrawCommand
                        (
                            indices.VertexCount, 
                            1, 0, 
                            indices.VertexIndex,
                            _resources.IndexOf(e.Value)
                        )
                    );
            }

            for (auto& stage : _staging)
            {
                stage.Value->Indexed.Update();
                stage.Value->NonIndexed.Update();
            }
        }
        //void SceneLayer3D::Update(const Resource<IRenderable>& entity)
        //{
        //    _resources.Update(entity);
        //    //if (!_entities.Contains(entity.ID())) { return; }
        //    //_updates.Append(entity);
        //}
        //void SceneLayer3D::Update(const Resource<IMaterial>& material)
        //{
        //    _resources.Update(material);
        //}



        /** PROTECTED UTILITIES **/
        //void SceneLayer3D::UpdateMaterial(const Resource<IRenderable>& entity)
        //{
        //    if (entity.IsNull() || entity->Material().IsNull())   { return; }
        //    _materials.Set(entity->Material().ID(), entity->Material()->Data());
        //}
        //void SceneLayer3D::UpdateTransforms(const Resource<IRenderable>& entity)
        //{
        //    if (entity.IsNull()) { return; }
        //    TransformData xforms =
        //    {
        //        entity->Model()                                     ? 
        //            entity->Model()->Transform().ToMatrix4x4()      : 
        //            Matrix4x4::Identity,
        //        entity->Material()                                  ? 
        //            entity->Material()->Transform().ToMatrix4x4()   : 
        //            Matrix4x4::Identity,
        //        entity->Transform().ToMatrix4x4()
        //    };

        //    _transforms.Set(entity.ID(), xforms);
        //}

        StageGroup3D* SceneLayer3D::CreateStage(PointTopologies topology)
        {
            StageGroup3D* stage = new StageGroup3D();
            stage->Indexed
                .Settings(Settings())
                .Topology(topology);

            stage->NonIndexed
                .Settings(Settings())
                .Topology(topology);

            _staging.Insert(topology, stage);
            return stage;
        }

    }
}