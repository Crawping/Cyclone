/* CHANGELOG
 * Written by Josh Grooms on 20170604
 */

#pragma once
#include "Collections/Set.h"
#include "Interfaces/IGeometric.h"
#include "Interfaces/IMaterial.h"
#include "Interfaces/IModel.h"
#include "Interfaces/IRenderable.h"
#include "Pipelines/GraphicsPipeline.h"
#include "Resources/Resource.h"



namespace Cyclone
{
    namespace Scenes
    {

        class ResourceManager;
        using namespace OpenGL;






        class ResourceManager
        {
            public:

                ResourceManager() { }
                ~ResourceManager()
                {
                    for (auto* v : _buffers)    { delete v; }
                    for (auto* v : _geometry)   { delete v; }
                    for (auto* v : _pipelines)  { delete v; }
                    for (auto* v : _textures)   { delete v; }
                }



                /** UTILITIES **/
                
                template<typename T>
                bool Contains(Resource<T> value)
                {
                    return Contains(value->_value);
                }
                template<typename T, typename ... U> 
                Resource<T> Create(U ... arguments)
                {
                    T* value = new T(arguments...);
                    Register(value);
                    return Resource<T>(value);
                }
                template<typename T>
                void Destroy(Resource<T> value)
                {
                    if (!Contains(value)) { return; }
                    Remove(value->_value);
                    delete value->_value;
                }

            private:

                Set<IGraphicsBuffer*>       _buffers;
                Set<IGeometric*>            _geometry;
                Set<GraphicsPipeline*>      _pipelines;
                Set<ITexture*>              _textures;




                bool Contains(IGraphicsBuffer* value)
                {
                    return _buffers.Contains(value);
                }
                bool Contains(GraphicsPipeline* value)
                {
                    return _pipelines.Contains(value);
                }
                bool Contains(IGeometric* value)
                {
                    return _geometry.Contains(value);
                }
                bool Contains(ITexture* value)
                {
                    return _textures.Contains(value);
                }

                void Register(GraphicsPipeline* value)
                {
                    if (!value) { return; }
                    _pipelines.Insert(value);
                }
                void Register(IGeometric* value)
                {
                    if (!value) { return; }
                    _geometry.Insert(value);
                }
                void Register(ITexture* value)
                {
                    if (!value) { return; }
                    _textures.Insert(value);
                }

                void Remove(IGraphicsBuffer* value)
                {
                    _buffers.Remove(value);
                }
                void Remove(GraphicsPipeline* value)
                {
                    _pipelines.Remove(value);
                }
                void Remove(IGeometric* value)
                {
                    _geometry.Remove(value);
                }
                void Remove(ITexture* value)
                {
                    _textures.Remove(value);
                }
        };
    }
}
