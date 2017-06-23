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
            auto buffers = SceneComponent3D::Buffers();
            buffers.Append({ _materials,    3 });
            buffers.Append({ _transforms,   4 });
            return buffers;
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
                stages.First().Append(Buffers());
            }

            return stages;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        SceneLayer3D::SceneLayer3D(const string& name, ISceneLayer& parent): 
            SceneComponent3D(name, parent)
        {

        }



        /** UTILITIES **/
        uint SceneLayer3D::IndexOf(const Resource<IMaterial>& material) const
        {
            return _materials.IndexOf(material.ID());
        }
        uint SceneLayer3D::IndexOf(const Resource<IRenderable>& entity) const
        {
            return _entities.IndexOf(entity.ID());
        }
        void SceneLayer3D::Insert(const string& name, ISceneComponent& stage)
        {
            _components.Insert(name, &stage);
        }
        void SceneLayer3D::Insert(const Resource<IRenderable>& entity)
        {
            if (entity.IsNull() || _entities.Contains(entity.ID())) { return; }
            _entities.Insert(entity.ID(), entity);
            SceneComponent3D::Insert(entity);
            Update(entity);
        }
        void SceneLayer3D::Remove(const string& name)
        {
            _components.Remove(name);
        }
        void SceneLayer3D::Update()
        {
            for (auto& c : _components.Values())
                c->Update();

            for (const auto& entity : _updates)
            {
                UpdateMaterial(entity);
                UpdateTransforms(entity);
            }

            _updates.Clear();
            _materials.Update();
            _transforms.Update();

            SceneComponent3D::Update();
        }
        void SceneLayer3D::Update(const Resource<IRenderable>& entity)
        {
            if (!_entities.Contains(entity.ID())) { return; }
            _updates.Append(entity);
        }



        /** PROTECTED UTILITIES **/
        void SceneLayer3D::UpdateMaterial(const Resource<IRenderable>& entity)
        {
            if (entity.IsNull() || entity->Material().IsNull())   { return; }
            _materials.Set(entity->Material().ID(), entity->Material()->Data());
        }
        void SceneLayer3D::UpdateTransforms(const Resource<IRenderable>& entity)
        {
            if (entity.IsNull()) { return; }
            TransformData xforms =
            {
                entity->Model()                                     ? 
                    entity->Model()->Transform().ToMatrix4x4()      : 
                    Matrix4x4::Identity,
                entity->Material()                                  ? 
                    entity->Material()->Transform().ToMatrix4x4()   : 
                    Matrix4x4::Identity,
                entity->Transform().ToMatrix4x4()
            };

            _transforms.Set(entity.ID(), xforms);
        }

    }
}