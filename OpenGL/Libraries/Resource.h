/* CHANGELOG
 * Written by Josh Grooms on 20170605
 */

#pragma once
#include "Collections/BST.h"
#include "Interfaces/ICallback.h"
#include "Interfaces/IGeometric.h"
#include "Interfaces/IMaterial.h"
#include "Interfaces/IModel.h"
#include "Interfaces/IRenderable.h"
#include "Interfaces/ITexture.h"
#include "IO/Functions.h"
#include "Libraries/Resource.h"
#include "Meta/Utilities.h"
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

                /** PROPERTIES **/
                bool IsNull()                               const { return _value == nullptr; }
                const string& Name()                        const { return _name; }



                /** CONSTRUCTOR **/
                Resource():
                    _name(""),
                    _value(nullptr)
                {

                }
                Resource(const string& name, T* value):     
                    _name(name),
                    _value(value)
                {

                }



                /** OPERATORS **/
                T* operator ->()                            { return _value; }
                const T* operator ->()                      const { return _value; }

                bool operator ==(const Resource& other)     const
                {
                    return (_name == other._name) && _value == other._value;
                }
                template<typename U>
                bool operator ==(const Resource<U>& other)  const { return false; }

                template<typename U>
                bool operator !=(const Resource<U>& other)  const { return !(operator ==(other)); }
        };


        class ResourceLibrary2
        {
            public:

                /** PROPERTIES **/
                uint BufferCount()      const { return _buffers.Count(); }
                uint Count()            const { return BufferCount() + GeometryCount() + PipelineCount() + TextureCount(); }
                uint GeometryCount()    const { return _geometry.Count(); }
                uint PipelineCount()    const { return _pipelines.Count(); }
                uint TextureCount()     const { return _textures.Count(); }
                


                /** CONSTRUCTOR & DESTRUCTOR **/
                ResourceLibrary2() { }
                ~ResourceLibrary2()
                {
                    for (auto v : _buffers.Values())     { delete v; }
                    for (auto v : _geometry.Values())    { delete v; }
                    for (auto v : _pipelines.Values())   { delete v; }
                    for (auto v : _textures.Values())    { delete v; }
                }



                /** UTILITIES **/
                template<typename T>
                bool Contains(Resource<T> value)                            const { return Contains(value._name, value._value); }
                template<typename T>
                bool Contains(const string& name)
                {
                    return
                        Meta::IsA<T, IGraphicsBuffer>()     ? _buffers.Contains(name)   :
                        Meta::IsA<T, IGeometric>()          ? _geometry.Contains(name)  :
                        Meta::IsA<T, GraphicsPipeline>()    ? _pipelines.Contains(name) :
                        Meta::IsA<T, ITexture>()            ? _textures.Contains(name)  : false;
                }
                template<typename T, typename ... U>
                Resource<T> Create(const string& name)
                {
                    T* value = new T();
                    Register(name, value);
                    return Resource<T>(name, value);
                }
                template<typename T, typename ... U>
                Resource<T> Create(const string& name, const ICallback<T, U...>& constructor, U ... arguments)
                {
                    T* value = new T();
                    *value = constructor(arguments...);
                    Register(name, value);
                    return Resource<T>(name, value);
                }
                template<typename T>
                void Destroy(Resource<T> value)
                {
                    if (!Contains(value)) { return; }
                    Meta::IsA<T, IGraphicsBuffer>()     ? _buffers.Remove(value.Name())     : 
                    Meta::IsA<T, IGeometric>()          ? _geometry.Remove(value.Name())    : 
                    Meta::IsA<T, GraphicsPipeline>()    ? _pipelines.Remove(value.Name())   : _textures.Remove(value.Name());

                    delete value._value;
                }
                template<typename T>
                Resource<T> Get(const string& name)
                {
                    return
                        !Contains<T>(name)                  ? Resource<T>(name, nullptr)                            : 
                        Meta::IsA<T, IGraphicsBuffer>()     ? Resource<T>(name, dynamic_cast<T*>(_buffers[name]))   :
                        Meta::IsA<T, IGeometric>()          ? Resource<T>(name, dynamic_cast<T*>(_geometry[name]))  :
                        Meta::IsA<T, GraphicsPipeline>()    ? Resource<T>(name, dynamic_cast<T*>(_pipelines[name])) :
                        Resource<T>(name, dynamic_cast<T*>(_textures[name]));
                }

            private:

                /** DATA **/
                BST<string, IGraphicsBuffer*>   _buffers;
                BST<string, IGeometric*>        _geometry;
                BST<string, GraphicsPipeline*>  _pipelines;
                BST<string, ITexture*>          _textures;



                /** UTILITIES **/
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
                    if (_buffers.Contains(key)) { delete _buffers[key]; }
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
                    if (Contains(key, value)) { delete value; }
                }
                void Destroy(const string& key, ITexture* value)
                {
                    if (Contains(key, value)) { delete value; }
                }

        };



    }
}