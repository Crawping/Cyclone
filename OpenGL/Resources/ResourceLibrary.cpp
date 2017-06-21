#include "Utilities.h"
#include "Resources/ResourceLibrary2.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** CONSTRUCTOR & DESTRUCTOR **/
        ResourceLibrary2::ResourceLibrary2()
        {
            uint idNull = hash("Null");
            _buffers.Insert     (idNull, std::move(Resource<IGraphicsBuffer,      true>()));
            _geometry.Insert    (idNull, std::move(Resource<IGeometric,           true>()));
            _materials.Insert   (idNull, std::move(Resource<IMaterial,            true>()));
            _pipelines.Insert   (idNull, std::move(Resource<IGraphicsPipeline,    true>()));
            _renderables.Insert (idNull, std::move(Resource<IRenderable,          true>()));
            _settings.Insert    (idNull, std::move(Resource<IGraphicsSettings,    true>()));
            _textures.Insert    (idNull, std::move(Resource<ITexture,             true>()));
        }
        ResourceLibrary2::~ResourceLibrary2()
        {
            //for (auto& v : _buffers.Values())        { delete v; }
            //for (auto& v : _geometry.Values())       { delete v; }
            //for (auto& v : _materials.Values())      { delete v; }
            //for (auto& v : _pipelines.Values())      { delete v; }
            //for (auto& v : _renderables.Values())    { delete v; }
            //for (auto& v : _settings.Values())       { delete v; }
            //for (auto& v : _textures.Values())       { delete v; }
        }



        /** PRIVATE UTILITIES **/
        void ResourceLibrary2::Insert(const string& key, IGraphicsBuffer* value)
        {
            //_buffers.Insert(key, value);
            _buffers.Insert(hash(key), std::move(Resource<IGraphicsBuffer, true>(key, value)));
        }
        void ResourceLibrary2::Insert(const string& key, IGraphicsPipeline* value)
        {
            //_pipelines.Insert(key, value);
            _pipelines.Insert(hash(key), std::move(Resource<IGraphicsPipeline, true>(key, value)));
        }
        void ResourceLibrary2::Insert(const string& key, IGraphicsSettings* value)
        {
            //_settings.Insert(key, value);
            _settings.Insert(hash(key), std::move(Resource<IGraphicsSettings, true>(key, value)));
        }
        void ResourceLibrary2::Insert(const string& key, IMaterial* value)
        {
            //_materials.Insert(key, value);
            _materials.Insert(hash(key), std::move(Resource<IMaterial, true>(key, value)));
        }
        void ResourceLibrary2::Insert(const string& key, IGeometric* value)
        {
            //_geometry.Insert(key, value);
            _geometry.Insert(hash(key), std::move(Resource<IGeometric, true>(key, value)));
        }
        void ResourceLibrary2::Insert(const string& key, IRenderable* value)
        {
            //_renderables.Insert(key, value);
            _renderables.Insert(hash(key), std::move(Resource<IRenderable, true>(key, value)));
        }
        void ResourceLibrary2::Insert(const string& key, ITexture* value)
        {
            //_textures.Insert(key, value);
            _textures.Insert(hash(key), std::move(Resource<ITexture, true>(key, value)));
        }

    }
}