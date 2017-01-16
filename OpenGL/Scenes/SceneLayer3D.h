/* CHANGELOG
 * Written by Josh Grooms on 20161219
 */

#pragma once
#include "Buffers/IndexBuffer.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/UniformData.h"
#include "Buffers/VertexBuffer.h"
#include "Collections/BST.h"
#include "Interfaces/ITransformable.h"
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
                OpenGLAPI void Insert(const string& name, ISceneComponent& stage)      override;
                OpenGLAPI void Remove(const string& name)                              override;
                OpenGLAPI void Remove(const IRenderable& entity)                       override;
                OpenGLAPI void Update()                                                override;
                OpenGLAPI void Update(const IRenderable& entity)                       override;

            protected:

                /** UTILITIES **/
                OpenGLAPI ResourceMapping& Register(const IRenderable& entity)          override;

                OpenGLAPI virtual void Register(ResourceMapping& map, const IGeometric& entity);
                OpenGLAPI virtual void Register(ResourceMapping& map, const IMaterial& material);
                OpenGLAPI virtual void Register(ResourceMapping& map, const IRenderable& entity);
                OpenGLAPI virtual void Register(ResourceMapping& map, const ITransformable& entity);

            private:

                /** BUFFERS **/
                ResourceLibrary<EntityData>         Entities;
                IndexBuffer                         Indices;
                ResourceLibrary<MaterialData>       Materials;
                ResourceLibrary<TransformData>      Transforms;
                VertexBuffer<Vertex>                Vertices;



                /** COLLECTIONS **/
                BST<string, ISceneComponent&>               _components;
                BST<const IRenderable*, ResourceMapping>   Mappings;





        };
    }
}
