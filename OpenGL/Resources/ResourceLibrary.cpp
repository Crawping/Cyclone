#include "Resources/ResourceLibrary2.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** CONSTRUCTOR & DESTRUCTOR **/
        ResourceLibrary2::ResourceLibrary2()
        {
            _buffers.Insert("Null", nullptr);
            _geometry.Insert("Null", nullptr);
            _materials.Insert("Null", nullptr);
            _pipelines.Insert("Null", nullptr);
            _renderables.Insert("Null", nullptr);
            _settings.Insert("Null", nullptr);
            _textures.Insert("Null", nullptr);
        }
        ResourceLibrary2::~ResourceLibrary2()
        {
            for (auto v : _buffers.Values())        { delete v; }
            for (auto v : _geometry.Values())       { delete v; }
            for (auto v : _materials.Values())      { delete v; }
            for (auto v : _pipelines.Values())      { delete v; }
            for (auto v : _renderables.Values())    { delete v; }
            for (auto v : _settings.Values())       { delete v; }
            for (auto v : _textures.Values())       { delete v; }
        }



        /** PRIVATE UTILITIES **/
        void ResourceLibrary2::Insert(const string& key, IGraphicsBuffer* value)
        {
            //if (_buffers.Contains(key)) { delete _buffers[key]; }
            _buffers.Insert(key, value);
        }
        void ResourceLibrary2::Insert(const string& key, GraphicsPipeline* value)
        {
            //if (_pipelines.Contains(key)) { delete _pipelines[key]; }
            _pipelines.Insert(key, value);
        }
        void ResourceLibrary2::Insert(const string& key, GraphicsSettings* value)
        {
            _settings.Insert(key, value);
        }
        void ResourceLibrary2::Insert(const string& key, IMaterial* value)
        {
            //if (_materials.Contains(key)) { delete _materials[key]; }
            _materials.Insert(key, value);
        }
        void ResourceLibrary2::Insert(const string& key, IGeometric* value)
        {
            //if (_geometry.Contains(key)) { delete _geometry[key]; }
            _geometry.Insert(key, value);
        }
        void ResourceLibrary2::Insert(const string& key, IRenderable* value)
        {
            //if (_renderables.Contains(key)) { delete _renderables[key]; }
            _renderables.Insert(key, value);
        }
        void ResourceLibrary2::Insert(const string& key, ITexture* value)
        {
            //if (_textures.Contains(key)) { delete _textures[key]; }
            _textures.Insert(key, value);
        }

    }
}