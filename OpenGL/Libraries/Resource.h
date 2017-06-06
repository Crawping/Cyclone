/* CHANGELOG
 * Written by Josh Grooms on 20170605
 */

#pragma once
#include "Collections/BST.h"
#include "Interfaces/IGeometric.h"
#include "Interfaces/IMaterial.h"
#include "Interfaces/IModel.h"
#include "Interfaces/IRenderable.h"
#include "Libraries/Resource.h"
#include "Pipelines/GraphicsPipeline.h"



namespace Cyclone
{
    namespace OpenGL
    {
        using namespace Utilities;

        template<typename T>
        struct Resource
        {
            friend class ResourceLibrary2;
            private:

                string  _name;
                T*      _value;

            public:

                const string& Name()                        const { return _name; }

                Resource(const string& name, T* value):     _value(value) { }

                const T* operator ->()                      const { return _value; }
                T* operator ->()                            { return _value; }
        };


        class ResourceLibrary2
        {
            public:

                uint BufferCount()      const { return _buffers.Count(); }
                uint Count()            const { return BufferCount() + GeometryCount() + PipelineCount() + TextureCount(); }
                uint GeometryCount()    const { return _geometry.Count(); }
                uint PipelineCount()    const { return _pipelines.Count(); }
                uint TextureCount()     const { return _textures.Count(); }
                
                ~ResourceLibrary2()
                {
                    for (auto v : _buffers)     { delete v.Value; }
                    for (auto v : _geometry)    { delete v.Value; }
                    for (auto v : _pipelines)   { delete v.Value; }
                    for (auto v : _textures)    { delete v.Value; }
                }

                template<typename T>
                bool Contains(Resource<T> value)                            const { return Contains(value._name, value._value); }
                template<typename T, typename ... U>
                Resource<T> Create(const string& name, U ... arguments)
                {
                    T* value = new T(arguments...);
                    Register(name, value);
                    return Resource<T>(name, value);
                }
                template<typename T>
                void Destroy(Resource<T> value)
                {
                    if (Contains(value._name, value._value)) 
                    {
                        Remove(value._name, value._value);
                        delete value._value; 
                    }
                }


            private:

                BST<string, IGraphicsBuffer*>   _buffers;
                BST<string, IGeometric*>        _geometry;
                BST<string, GraphicsPipeline*>  _pipelines;
                BST<string, ITexture*>          _textures;

                bool Contains(const string& key, IGraphicsBuffer* value)    const
                {
                    return _buffers.Contains(key) && _buffers[key] == value;
                }
                bool Contains(const string& key, GraphicsPipeline* value)   const
                {
                    return _pipelines.Contains(key) && _pipelines[key] == value;
                }
                bool Contains(const string& key, IGeometric* value)         const
                {
                    return _geometry.Contains(key) && _geometry[key] == value;
                }
                bool Contains(const string& key, ITexture* value)           const
                {
                    return _textures.Contains(key) && _textures[key] == value;
                }

                void Register(const string& key, IGraphicsBuffer* value)
                {
                    if (_buffers.Contains(key) { delete _buffers[key]; }
                    _buffers.Insert(key, value);
                }
                void Register(const string& key, GraphicsPipeline* value)
                {
                    if (_pipelines.Contains(key)) { delete _pipelines[key]; }
                    _pipelines.Insert(key, value);
                }
                void Register(const string& key, IGeometric* value)
                {
                    if (_geometry.Contains(key)) { delete _geometry[key]; }
                    _geometry.Insert(key, value);
                }
                void Register(const string& key, ITexture* value)
                {
                    if (_textures.Contains(key)) { delete _textures[key]; }
                    _textures.Insert(key, value);
                }

                void Remove(const string& key, IGraphicsBuffer* value)      { _buffers.Remove(key); }
                void Remove(const string& key, GraphicsPipeline* value)     { _pipelines.Remove(key); }
                void Remove(const string& key, IGeometric* value)           { _geometry.Remove(key); }
                void Remove(const string& key, ITexture* value)             { _textures.Remove(key); }

                void Destroy(const string& key, IGraphicsBuffer* value)
                {
                    if (Contains(key, value)) { delete value; }
                }
                void Destroy(const string& key, GraphicsPipeline* value)
                {
                    if (Contains(key, value)) { delete value; }
                }
                void Destroy(const string& key, IGeometric* value)
                {

                }
                void Destroy(const string& key, ITexture* value)
                {

                }

        };



    }
}