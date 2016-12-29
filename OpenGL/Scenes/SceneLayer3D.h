/* CHANGELOG
 * Written by Josh Grooms on 20161219
 */

#pragma once
#include "Collections/BST.h"
#include "GraphicsSettings.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/UniformData.h"
#include "Buffers/VertexBuffer.h"
#include "Interfaces/IGeometric.h"
#include "Interfaces/IScene.h"
#include "Libraries/ResourceLibrary.h"
#include "Pipelines/RenderStage3D.h"
#include "Scenes/SceneComponent3D.h"




namespace Cyclone
{
    namespace OpenGL
    {
        class ITransformable;
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
                OpenGLAPI void Update()                                                override;
                OpenGLAPI void Update(const IRenderable& entity)                       override;

            protected:
                
                OpenGLAPI ResourceMapping& Register(const IRenderable& entity)          override;

            private:

                /** BUFFERS **/
                ResourceLibrary<EntityData>         Entities;
                IndexBuffer                         Indices;
                ResourceLibrary<MaterialData>       Materials;
                UniformBuffer<TransformData>        Transforms;
                VertexBuffer<Vertex::Standard>      Vertices;



                /** COLLECTIONS **/
                BST<string, ISceneComponent&>               _components;
                BST<const IRenderable*, ResourceMapping>   Mappings;



                /** UTILITIES **/
                void Register(ResourceMapping& map, const IGeometric& entity);
                void Register(ResourceMapping& map, const IMaterial& material);
                void Register(ResourceMapping& map, const ITransformable& entity);

        };
    }
}
