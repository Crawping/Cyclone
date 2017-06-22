#include "Utilities.h"
#include "Resources/ResourceLibrary.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** CONSTRUCTOR & DESTRUCTOR **/
        ResourceLibrary::ResourceLibrary()
        {
            uint idNull = hash("Null");
            Insert("Null", (IGraphicsBuffer*)nullptr);
            Insert("Null", (IGeometric*)nullptr);
            Insert("Null", (IMaterial*)nullptr);
            Insert("Null", (IModel*)nullptr);
            Insert("Null", (IGraphicsPipeline*)nullptr);
            Insert("Null", (IRenderable*)nullptr);
            Insert("Null", (IGraphicsSettings*)nullptr);
            Insert("Null", (ITexture*)nullptr);
        }



        /** PRIVATE UTILITIES **/
        void ResourceLibrary::Insert(const string& key, IGraphicsBuffer* value)
        {
            _buffers.Insert(hash(key), std::move(UniqueResource<IGraphicsBuffer>(key, value)));
        }
        void ResourceLibrary::Insert(const string& key, IGraphicsPipeline* value)
        {
            _pipelines.Insert(hash(key), std::move(UniqueResource<IGraphicsPipeline>(key, value)));
        }
        void ResourceLibrary::Insert(const string& key, IGraphicsSettings* value)
        {
            _settings.Insert(hash(key), std::move(UniqueResource<IGraphicsSettings>(key, value)));
        }
        void ResourceLibrary::Insert(const string& key, IMaterial* value)
        {
            _materials.Insert(hash(key), std::move(UniqueResource<IMaterial>(key, value)));
        }
        void ResourceLibrary::Insert(const string& key, IModel* value)
        {
            _models.Insert(hash(key), std::move(UniqueResource<IModel>(key, value)));
        }
        void ResourceLibrary::Insert(const string& key, IGeometric* value)
        {
            _geometry.Insert(hash(key), std::move(UniqueResource<IGeometric>(key, value)));
        }
        void ResourceLibrary::Insert(const string& key, IRenderable* value)
        {
            _renderables.Insert(hash(key), std::move(UniqueResource<IRenderable>(key, value)));
        }
        void ResourceLibrary::Insert(const string& key, ITexture* value)
        {
            _textures.Insert(hash(key), std::move(UniqueResource<ITexture>(key, value)));
        }

    }
}