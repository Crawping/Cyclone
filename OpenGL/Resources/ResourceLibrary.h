/* CHANGELOG
 * Written by Josh Grooms on 20170607
 */

#pragma once
//#include "GraphicsSettings.h"
#include "Utilities.h"
#include "Collections/BST.h"
#include "Interfaces/ICallback.h"
#include "Interfaces/IGeometric.h"
#include "Interfaces/IGraphicsBuffer.h"
#include "Interfaces/IGraphicsPipeline.h"
#include "Interfaces/IGraphicsSettings.h"
#include "Interfaces/IMaterial.h"
#include "Interfaces/IModel.h"
#include "Interfaces/IRenderable.h"
#include "Interfaces/ITexture.h"
#include "Meta/Utilities.h"
#include "Resources/Resource.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class ResourceLibrary
        {
            public:

                /** PROPERTIES **/
                uint BufferCount()      const { return _buffers.Count() - 1; }
                uint Count()            const 
                { 
                    return 
                        BufferCount() + GeometryCount() + MaterialCount() + 
                        ModelCount() + PipelineCount() + RenderableCount() + 
                        TextureCount() + SettingsCount();
                }
                uint GeometryCount()    const { return _geometry.Count() - 1; }
                uint MaterialCount()    const { return _materials.Count() - 1; }
                uint ModelCount()       const { return _models.Count() - 1; }
                uint PipelineCount()    const { return _pipelines.Count() - 1; }
                uint RenderableCount()  const { return _renderables.Count() - 1; }
                uint SettingsCount()    const { return _settings.Count() - 1; }
                uint TextureCount()     const { return _textures.Count() - 1; }
                


                /** CONSTRUCTOR & DESTRUCTOR **/
                OpenGLAPI ResourceLibrary();
                ResourceLibrary(const ResourceLibrary& other)         = delete;



                /** UTILITIES **/
                /// <summary> Determines whether a particular resource is stored within the library. </summary>
                /// <returns> A Boolean <c>true</c> if the resource is stored within the library, or <c>false</c> otherwise. </returns>
                /// <param name="value"> An existing resource handle. </param>
                template<typename T> bool Contains(Component<T> value)  const 
                {
                    auto r = Get<T>(value.ID());
                    return !r.IsNull() && (r == value);
                }
                /// <summary> Determines whether a particular resource is stored within the library. </summary>
                /// <returns> A Boolean <c>true</c> if the resource is stored within the library, or <c>false</c> otherwise. </returns>
                /// <typeparam name="T"> The type of the desired resource. </typeparam>
                /// <param name="name"> The string identifier of the resource. </param>
                template<typename T> bool Contains(const string& name)  const
                {
                    return Contains<T>(hash(name));
                }

                template<typename T> bool Contains(uint key)            const
                {
                    return
                        Meta::IsA<T, IGraphicsBuffer>()     ? _buffers.Contains(key)        :
                        Meta::IsA<T, IGeometric>()          ? _geometry.Contains(key)       :
                        Meta::IsA<T, IMaterial>()           ? _materials.Contains(key)      :
                        Meta::IsA<T, IModel>()              ? _models.Contains(key)         :
                        Meta::IsA<T, IGraphicsPipeline>()   ? _pipelines.Contains(key)      :
                        Meta::IsA<T, IRenderable>()         ? _renderables.Contains(key)    :
                        Meta::IsA<T, IGraphicsSettings>()   ? _settings.Contains(key)       :
                        Meta::IsA<T, ITexture>()            ? _textures.Contains(key)       : false;
                }
                /// <summary> Creates a new graphics resource that can be used on the GPU. </summary>
                template<typename T> Component<T> Create(const string& name)
                {
                    T* value = new T();
                    return Register<T>(name, value);
                }
                /// <summary> Creates a new graphics resource that can be used on the GPU. </summary>
                template<typename T, typename ... U>
                Component<T> Create(const string& name, const ICallback<T, U...>& constructor, U ... arguments)
                {
                    T* value = new T(constructor(arguments...));
                    return Register<T>(name, value);
                }
                /// <summary> Destroys an existing graphics resource that is stored within the library. </summary>
                template<typename T> void Destroy(Component<T> value)
                {
                    //const string& key = value.Name();
                    uint key = value.ID();
                    if ( value.IsNull() || !Contains<T>(key) ) { return; }

                    Meta::IsA<T, IGraphicsBuffer>()     ? _buffers.Remove(key)      :
                    Meta::IsA<T, IGeometric>()          ? _geometry.Remove(key)     :
                    Meta::IsA<T, IMaterial>()           ? _materials.Remove(key)    :
                    Meta::IsA<T, IModel>()              ? _models.Remove(key)       :
                    Meta::IsA<T, IGraphicsPipeline>()   ? _pipelines.Remove(key)    : 
                    Meta::IsA<T, IRenderable>()         ? _renderables.Remove(key)  : 
                    Meta::IsA<T, IGraphicsSettings>()   ? _settings.Remove(key)     : _textures.Remove(key);
                }
                /// <summary> Acquires a particular graphics resource stored within the library. </summary>
                template<typename T> Component<T> Get(const string& name)   const { return Get<T>(hash(name)); }

                template<typename T> Component<T> Get(uint key)             const
                {
                    return Component<T>(key, Contains<T>(key) ? const_cast<T*>(Access<T>(key)) : nullptr);
                }
                /// <summary> Checks an externally created resource into the library for management. </summary>
                /// <returns> A resource handle that represents the inputted value. </returns>
                /// <param name="name"> The desired name of the resource. </param>
                /// <param name="value"> A pointer to a resource constructed externally on the heap. </param>
                /// <remarks> Naming conflicts are resolved by deleting and overwriting the previously stored value. </remarks>
                template<typename T> Component<T> Register(const string& name, T* value)
                {
                    if (!value || (name == "Null"))
                        return Component<T>(name, nullptr);

                    Insert(name, value);
                    return Component<T>(name, value);
                }
                
            private:

                /** DATA **/
                BST<uint, Resource<IGraphicsBuffer, true>>      _buffers;
                BST<uint, Resource<IGeometric, true>>           _geometry;
                BST<uint, Resource<IMaterial, true>>            _materials;
                BST<uint, Resource<IModel, true>>               _models;
                BST<uint, Resource<IGraphicsPipeline, true>>    _pipelines;
                BST<uint, Resource<IRenderable, true>>          _renderables;
                BST<uint, Resource<IGraphicsSettings, true>>    _settings;
                BST<uint, Resource<ITexture, true>>             _textures;



                /** UTILITIES **/
                template<typename T> const T* Access(uint key)  const
                {
                    return
                        Meta::IsA<T, IGraphicsBuffer>()     ? dynamic_cast<const T*>(&*_buffers[key])     :
                        Meta::IsA<T, IGeometric>()          ? dynamic_cast<const T*>(&*_geometry[key])    :
                        Meta::IsA<T, IMaterial>()           ? dynamic_cast<const T*>(&*_materials[key])   :
                        Meta::IsA<T, IModel>()              ? dynamic_cast<const T*>(&*_models[key])      :
                        Meta::IsA<T, IGraphicsPipeline>()   ? dynamic_cast<const T*>(&*_pipelines[key])   :
                        Meta::IsA<T, IRenderable>()         ? dynamic_cast<const T*>(&*_renderables[key]) :
                        Meta::IsA<T, IGraphicsSettings>()   ? dynamic_cast<const T*>(&*_settings[key])    : 
                        dynamic_cast<const T*>(&*_textures[key]);
                }

                OpenGLAPI void Insert(const string& key, IGraphicsBuffer* value);
                OpenGLAPI void Insert(const string& key, IGraphicsPipeline* value);
                OpenGLAPI void Insert(const string& key, IGraphicsSettings* value);
                OpenGLAPI void Insert(const string& key, IGeometric* value);
                OpenGLAPI void Insert(const string& key, IMaterial* value);
                OpenGLAPI void Insert(const string& key, IModel* value);
                OpenGLAPI void Insert(const string& key, IRenderable* value);
                OpenGLAPI void Insert(const string& key, ITexture* value);

        };
    }
}