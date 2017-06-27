#include "Interfaces/IMaterial.h"
#include "Interfaces/IModel.h"
#include "Interfaces/ITexture.h"
#include "Resources/RenderLayer.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PUBLIC UTILITIES **/
        void RenderLayer::Insert(const Resource<IRenderable>& entity)
        {
            if (entity.IsNull() || Contains(entity)) { return; }
            _entities.Set(entity.ID(), EntityData());
            _transforms.Set(entity.ID(), TransformData());
            Insert(entity->Material());
            _entityUpdates.Append(entity);
        }
        void RenderLayer::Insert(const Resource<IMaterial>& material)
        {
            if (material.IsNull() || Contains(material)) { return; }
            _materials.Set(material.ID(), MaterialData());
            _materialUpdates.Append(material);
        }
        void RenderLayer::Update()
        {
            for (const auto& entity : _entityUpdates)
            {
                UpdateEntityData(entity);
                UpdateTransformData(entity);
            }

            for (const auto& material : _materialUpdates)
                UpdateMaterialData(material);

            _entityUpdates.Clear();
            _materialUpdates.Clear();

            _entities.Update();
            _materials.Update();
            _transforms.Update();
        }
        void RenderLayer::Update(const Resource<IRenderable>& entity)
        {
            if (!Contains(entity)) { return; }
            _entityUpdates.Append(entity);
        }
        void RenderLayer::Update(const Resource<IMaterial>& material)
        {
            if (!Contains(material)) { return; }
            _materialUpdates.Append(material);
        }



        /** PRIVATE UTILITIES **/
        bool RenderLayer::Contains(const Resource<IRenderable>& entity) const
        {
            return _entities.Contains(entity.ID());
        }
        bool RenderLayer::Contains(const Resource<IMaterial>& material) const
        {
            return _materials.Contains(material.ID());
        }

        void RenderLayer::UpdateEntityData(const Resource<IRenderable>& entity)
        {
            EntityData data = 
            {
                Contains(entity->Material()) ? _materials.IndexOf(entity->Material().ID()) : 0,
                _transforms.IndexOf(entity.ID()),
            };

            _entities.Set(entity.ID(), data);
        }
        void RenderLayer::UpdateMaterialData(const Resource<IMaterial>& material)
        {
            MaterialData data =
            {
                material->PrimaryColor(),
                material->SecondaryColor(),
                material->Texture() ? material->Texture()->Handle() : 0,
                material->Ambience(),
                material->SpecularPower(),
                material->Texture() != nullptr,
            };

            _materials.Set(material.ID(), data);
        }
        void RenderLayer::UpdateTransformData(const Resource<IRenderable>& entity)
        {
            TransformData data =
            {
                entity->Model()                                     ? 
                    entity->Model()->Transform().ToMatrix4x4()      : 
                    Matrix4x4::Identity,
                entity->Material()                                  ? 
                    entity->Material()->Transform().ToMatrix4x4()   : 
                    Matrix4x4::Identity,
                entity->Transform().ToMatrix4x4()
            };

            _transforms.Set(entity.ID(), data);
        }

    }
}