/* CHANGELOG
 * Written by Josh Grooms on 20170623
 */

#pragma once
#include "Buffers/IndexBuffer.h"
#include "Buffers/UniformData.h"
#include "Buffers/UniformMap.h"
#include "Buffers/VertexBuffer.h"
#include "GL/OpenGLAPI.h"
#include "Interfaces/IRenderable.h"
#include "Interfaces/IMaterial.h"
#include "Interfaces/IGeometric.h"
#include "Resources/Resource.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class RenderLayer
        {
            public:

                OpenGLAPI virtual List<BufferBinding> Buffers() const;
                


                /** CONSTRUCTOR **/
                RenderLayer() { }
                virtual ~RenderLayer() { }



                /** UTILITIES **/
                OpenGLAPI virtual uint IndexOf(const Resource<IMaterial>& material) const;
                OpenGLAPI virtual uint IndexOf(const Resource<IRenderable>& entity) const;

                OpenGLAPI virtual void Insert(const Resource<IMaterial>& material);
                OpenGLAPI virtual void Insert(const Resource<IRenderable>& entity);
                //OpenGLAPI virtual void MappingOf

                OpenGLAPI virtual void Update();
                OpenGLAPI virtual void Update(const Resource<IRenderable>& entity);
                OpenGLAPI virtual void Update(const Resource<IMaterial>& material);

            private:

                UniformMap<uint, EntityData>        _entities;
                UniformMap<uint, MaterialData>      _materials;
                UniformMap<uint, TransformData>     _transforms;
                

                ArrayList<Resource<IRenderable>>    _entityUpdates;
                ArrayList<Resource<IMaterial>>      _materialUpdates;


                OpenGLAPI bool Contains(const Resource<IRenderable>& entity) const;
                OpenGLAPI bool Contains(const Resource<IMaterial>& material) const;

                OpenGLAPI void UpdateEntityData(const Resource<IRenderable>& entity);
                OpenGLAPI void UpdateMaterialData(const Resource<IMaterial>& material);
                OpenGLAPI void UpdateTransformData(const Resource<IRenderable>& entity);
        };
    }
}
