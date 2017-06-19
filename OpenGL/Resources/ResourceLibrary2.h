/* CHANGELOG
 * Written by Josh Grooms on 20170607
 */

#pragma once
#include "GraphicsSettings.h"
#include "Collections/BST.h"
#include "Interfaces/ICallback.h"
#include "Interfaces/IGeometric.h"
#include "Interfaces/IMaterial.h"
#include "Interfaces/IModel.h"
#include "Interfaces/IRenderable.h"
#include "Interfaces/ITexture.h"
#include "Meta/Utilities.h"
#include "Pipelines/GraphicsPipeline.h"
#include "Resources/Resource.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class ResourceLibrary2
        {
            public:

                /** PROPERTIES **/
                uint BufferCount()      const { return _buffers.Count() - 1; }
                uint Count()            const 
                { 
                    return 
                        BufferCount() + GeometryCount() + MaterialCount() + 
                        PipelineCount() + RenderableCount() + TextureCount() + 
                        SettingsCount();
                }
                uint GeometryCount()    const { return _geometry.Count() - 1; }
                uint MaterialCount()    const { return _materials.Count() - 1; }
                uint PipelineCount()    const { return _pipelines.Count() - 1; }
                uint RenderableCount()  const { return _renderables.Count() - 1; }
                uint SettingsCount()    const { return _settings.Count() - 1; }
                uint TextureCount()     const { return _textures.Count() - 1; }
                


                /** CONSTRUCTOR & DESTRUCTOR **/
                OpenGLAPI ResourceLibrary2();
                ResourceLibrary2(const ResourceLibrary2& other) = delete;
                OpenGLAPI ~ResourceLibrary2();



                /** UTILITIES **/
                /// <summary> Determines whether a particular resource is stored within the library. </summary>
                /// <returns> A Boolean <c>true</c> if the resource is stored within the library, or <c>false</c> otherwise. </returns>
                /// <param name="value"> An existing resource handle. </param>
                template<typename T> bool Contains(Resource<T> value) const 
                {
                    auto r = Get<T>(value.Name());
                    return !r.IsNull() && (r._value == value._value);
                }
                /// <summary> Determines whether a particular resource is stored within the library. </summary>
                /// <returns> A Boolean <c>true</c> if the resource is stored within the library, or <c>false</c> otherwise. </returns>
                /// <typeparam name="T"> The type of the desired resource. </typeparam>
                /// <param name="name"> The string identifier of the resource. </param>
                template<typename T> bool Contains(const string& name) const
                {
                    return
                        Meta::IsA<T, IGraphicsBuffer>()     ? _buffers.Contains(name)       :
                        Meta::IsA<T, IGeometric>()          ? _geometry.Contains(name)      :
                        Meta::IsA<T, IMaterial>()           ? _materials.Contains(name)     :
                        Meta::IsA<T, GraphicsPipeline>()    ? _pipelines.Contains(name)     :
                        Meta::IsA<T, IRenderable>()         ? _renderables.Contains(name)   : 
                        Meta::IsA<T, GraphicsSettings>()    ? _settings.Contains(name)      :
                        Meta::IsA<T, ITexture>()            ? _textures.Contains(name)      : false;
                }
                /// <summary> Creates a new graphics resource that can be used on the GPU. </summary>
                template<typename T> Resource<T> Create(const string& name)
                {
                    T* value = new T();
                    return Register<T>(name, value);
                }
                /// <summary> Creates a new graphics resource that can be used on the GPU. </summary>
                template<typename T, typename ... U>
                Resource<T> Create(const string& name, const ICallback<T, U...>& constructor, U ... arguments)
                {
                    T* value = new T(constructor(arguments...));
                    return Register<T>(name, value);
                }
                /// <summary> Destroys an existing graphics resource that is stored within the library. </summary>
                template<typename T> void Destroy(Resource<T> value)
                {
                    const string& key = value.Name();
                    if ( value.IsNull() || !Contains(value) ) { return; }

                    Meta::IsA<T, IGraphicsBuffer>()     ? _buffers.Remove(key)      :
                    Meta::IsA<T, IGeometric>()          ? _geometry.Remove(key)     :
                    Meta::IsA<T, IMaterial>()           ? _materials.Remove(key)    :
                    Meta::IsA<T, GraphicsPipeline>()    ? _pipelines.Remove(key)    : 
                    Meta::IsA<T, IRenderable>()         ? _renderables.Remove(key)  : 
                    Meta::IsA<T, GraphicsSettings>()    ? _settings.Remove(key)     : _textures.Remove(key);

                    delete value._value;
                }
                /// <summary> Acquires a particular graphics resource stored within the library. </summary>
                template<typename T> Resource<T> Get(const string& name) const
                {
                    return
                        !Contains<T>(name)                  ? Resource<T>(name, nullptr)                                : 
                        Meta::IsA<T, IGraphicsBuffer>()     ? Resource<T>(name, dynamic_cast<T*>(_buffers[name]))       :
                        Meta::IsA<T, IMaterial>()           ? Resource<T>(name, dynamic_cast<T*>(_materials[name]))     :
                        Meta::IsA<T, IGeometric>()          ? Resource<T>(name, dynamic_cast<T*>(_geometry[name]))      :
                        Meta::IsA<T, GraphicsPipeline>()    ? Resource<T>(name, dynamic_cast<T*>(_pipelines[name]))     :
                        Meta::IsA<T, IRenderable>()         ? Resource<T>(name, dynamic_cast<T*>(_renderables[name]))   : 
                        Meta::IsA<T, GraphicsSettings>()    ? Resource<T>(name, dynamic_cast<T*>(_settings[name]))      :
                        Meta::IsA<T, ITexture>()            ? Resource<T>(name, dynamic_cast<T*>(_textures[name]))      : 
                        Resource<T>(name, nullptr);
                }
                template<typename T> Resource<T> Register(const string& name, T* value)
                {
                    if (!value || (name == "Null"))
                        return Resource<T>(name, nullptr);

                    auto r = Get<T>(name);
                    if (!r.IsNull() && r._value != value)
                        delete r._value;

                    Insert(name, value);
                    return Resource<T>(name, value);
                }
                
            private:

                /** DATA **/
                BST<string, IGraphicsBuffer*>   _buffers;
                BST<string, IGeometric*>        _geometry;
                BST<string, IMaterial*>         _materials;
                BST<string, GraphicsPipeline*>  _pipelines;
                BST<string, IRenderable*>       _renderables;
                BST<string, GraphicsSettings*>  _settings;
                BST<string, ITexture*>          _textures;



                /** UTILITIES **/
                OpenGLAPI void Insert(const string& key, IGraphicsBuffer* value);
                OpenGLAPI void Insert(const string& key, GraphicsPipeline* value);
                OpenGLAPI void Insert(const string& key, GraphicsSettings* value);
                OpenGLAPI void Insert(const string& key, IMaterial* value);
                OpenGLAPI void Insert(const string& key, IGeometric* value);
                OpenGLAPI void Insert(const string& key, IRenderable* value);
                OpenGLAPI void Insert(const string& key, ITexture* value);

        };
    }
}