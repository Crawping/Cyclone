/* CHANGELOG 
 * Written by Josh Grooms on 20170622
 */

#pragma once
#include "Buffers/IndexBuffer.h"
#include "Buffers/UniformData.h"
#include "Buffers/UniformMap.h"
#include "Buffers/VertexBuffer.h"
#include "GL/OpenGLAPI.h"
#include "Interfaces/IRenderable.h"
#include "Interfaces/IGeometric.h"
#include "Resources/ResourceLibrary.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class RenderLayer3D
        {
            public:

                template<typename T> using ResourceList = List< Resource<T> >;



                ResourceList<IRenderStage> Stages()                             const { return _stages.Values(); }




                template<typename T> 
                Resource<T> Create(const string& name)                          { return _resources.Create<T>(name); }
                template<typename T, typename ... U>
                Resource<T> Create(const string& name, const ICallback<T, U...>& constructor, U ... arguments)
                {
                    auto r = _resource.Create<T, U...>(name, constructor, arguments...);
                    Insert(r);
                    return r;
                }
                template<typename T> Resource<T> Get(const string& name)        { return _resources.Get<T>(name); }


                OpenGLAPI void Update();

            private:

                ResourceLibrary                     _resources;

                UniformMap<uint, EntityData>        _entities;
                IndexBuffer                         _indices;
                UniformMap<uint, MaterialData>      _materials;
                UniformMap<uint, TransformData>     _transforms;
                VertexBuffer<Vertex>                _vertices;
                
                BST<uint, Resource<IGeometric>>     _geometry;
                BST<uint, Resource<IRenderable>>    _renderables;
                BST<uint, Resource<IRenderStage>>   _stages;


                template<typename T> void Insert(const Resource<T>&) const { }

                OpenGLAPI void Insert(const Resource<IRenderable>& entity);
                OpenGLAPI void Insert(const Resource<IMaterial>& material);
                OpenGLAPI void Insert(const Resource<IGeometric>& geometry);

                OpenGLAPI void Update(const Resource<IRenderable>& entity);
                OpenGLAPI void Update(const Resource<IMaterial>& material);
                OpenGLAPI void Update(const Resource<IGeometric>& geometry);
        };
    }
}
