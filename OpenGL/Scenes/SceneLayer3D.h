/* CHANGELOG
 * Written by Josh Grooms on 20161219
 */

#pragma once
#include "Buffers/IndexBuffer.h"
#include "Buffers/UniformMap.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/UniformData.h"
#include "Buffers/VertexBuffer.h"
#include "Collections/BST.h"
#include "Libraries/ResourceLibrary.h"
#include "Scenes/SceneComponent3D.h"




namespace Cyclone
{
    namespace OpenGL
    {
        /** FORWARD DECLARATIONS **/
        class IGeometric;
        class IMaterial;
        class ITransformable;
        struct MaterialData;
        struct ResourceMapping;


        class SceneLayer3D :
            public SceneComponent3D,
            public virtual ISceneLayer
        {

            public:

                /** PROPERTIES **/
                OpenGLAPI List<BufferBinding> Buffers()                 const;
                OpenGLAPI List<ISceneComponent&> Components()           const override;
                OpenGLAPI List<IRenderStage&> Stages()                  const override;



                /** CONSTRUCTOR & DESTRUCTOR **/
                OpenGLAPI SceneLayer3D(const string& name, ISceneLayer& parent);
                virtual ~SceneLayer3D() { }



                /** UTILITIES **/
                using SceneComponent3D::Insert;
                OpenGLAPI uint IndexOf(const Resource<IRenderable>& entity)             const override;
                OpenGLAPI uint IndexOf(const Resource<IMaterial>& material)             const override;
                OpenGLAPI void Insert(const string& name, ISceneComponent& stage)       override;
                OpenGLAPI void Insert(const Resource<IRenderable>& entity)              override;
                OpenGLAPI void Remove(const string& name)                               override;
                OpenGLAPI void Update()                                                 override;
                OpenGLAPI void Update(const Resource<IRenderable>& entity)              override;;

            protected:

                /** UTILITIES **/
                OpenGLAPI virtual void UpdateMaterial(const Resource<IRenderable>& entity);
                OpenGLAPI virtual void UpdateTransforms(const Resource<IRenderable>& entity);

            private:

                /** BUFFERS **/
                UniformMap<uint, MaterialData>      _materials;
                UniformMap<uint, TransformData>     _transforms;


                BST<uint, Resource<IRenderable>>    _entities;
                ArrayList<Resource<IRenderable>>    _updates;



                /** COLLECTIONS **/
                BST<string, ISceneComponent*>              _components;
                BST<const IRenderable*, ResourceMapping>   Mappings;





        };
    }
}
