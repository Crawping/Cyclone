/* CHANGELOG
 * Written by Josh Grooms on 20160724
 */

#pragma once
#include "GraphicsSettings.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/UniformData.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/VertexBuffer.h"
#include "Collections/List.h"
#include "Geometry/Vertex.h"
#include "GL/OpenGLAPI.h"
#include "Interfaces/IRenderable.h"
#include "Interfaces/IUpdatable.h"
#include "Libraries/ResourceLibrary.h"
#include "Pipelines/RenderStage3D.h"
#include "Scenes/SceneLayer3D.h"

#include <map>



namespace Cyclone
{
    namespace OpenGL
    {
        class IRenderStage;


        struct ResourceMapping
        {
            uint EntityIndex;
            uint IndicesCount;
            uint IndicesIndex;
            uint TransformIndex;
            uint VertexCount;
            uint VertexIndex;

            RegistryKey<MaterialData>   MaterialKey;
            VertexTopologies            Topology;
        };



        /// <summary> A 3D scene representing a collection of renderable objects. </summary>
        class Scene3D : public IScene
        {

            public:

                OpenGLAPI List<IRenderStage&> Stages() const override;

                bool NeedsUpdate()                              const { return true; }
                const GraphicsSettings& Settings()              const { return _settings; }

                Scene3D& IsBlendEnabled(bool value)             { _settings.IsBlendEnabled = value; return *this; }
                Scene3D& IsDepthTestEnabled(bool value)         { _settings.IsDepthTestEnabled = value; return *this; }
                Scene3D& IsStencilTestEnabled(bool value)       { _settings.IsStencilTestEnabled = value; return *this; }
                Scene3D& IsVisible(bool value)                  { _isVisible = value; return *this; }

                Scene3D& CullingMode(CullingModes value)        { _settings.CullingMode = value; return *this; }
                Scene3D& Pipeline(GraphicsPipeline* value)      { _settings.Pipeline = value; return *this; }
                Scene3D& Projection(ITransformation3D* value)   { _settings.Projection = value; return *this; }
                Scene3D& Target(FrameBuffer* value)             { _settings.Target = value; return *this; }
                Scene3D& View(ITransformation3D* value)         { _settings.View = value; return *this; }



                /** CONSTRUCTOR **/
                /// <summary> Constructs an empty scene object that can be populated with renderable entities. </summary>
                OpenGLAPI Scene3D();
                OpenGLAPI ~Scene3D();



                /** UTILITIES **/
                /// <summary> Adds a renderable entity to this scene. </summary>
                /// <param name="entity">
                ///     A reference to the renderable entity that will be added to the scene. If this entity already exists
                ///     within this collection (i.e. it has been added previously), then its corresponding data store will
                ///     be updated. Otherwise, this method generates a new entry in the scene's data collection to hold the
                ///     necessary rendering information for the entity.
                /// </param>
                OpenGLAPI void Add(const IRenderable3D<Vector3>& entity);
                OpenGLAPI void Remove(const IRenderable3D<Vector3>& entity);
                OpenGLAPI void Update();
                OpenGLAPI void Update(const IRenderable3D<Vector3>& entity);

                //OpenGLAPI void Add(const string& stage, const IRenderable3D<Vector3>& entity);
                //OpenGLAPI void CreateStage(const string& name);
                //OpenGLAPI void Settings(const string& stage, const GraphicsSettings& value);


                OpenGLAPI void Insert(const string& name, ISceneComponent& component);
                OpenGLAPI void Associate(const string& name, const IRenderable3D<Vector3>& entity);


            private:

                /** PROPERTY DATA **/
                bool                _isVisible;
                GraphicsSettings    _settings;



                /** BUFFERED DATA **/
                UniformBuffer<EntityData>           Entities;
                IndexBuffer                         Indices;
                ResourceLibrary<MaterialData>       Materials;
                UniformBuffer<TransformData>        Transforms;
                VertexBuffer<Vertex::Standard>      Vertices;



                /** BUFFER & STAGE MAPPINGS **/
                //std::map<VertexTopologies, SceneLayer3D*>                           Layers;
                BST<string, ISceneComponent&>       Components;
                BST<const IRenderable3D<Vector3>*, ResourceMapping> TempIndices;


                std::map<const IRenderable3D<Vector3>*, ResourceMapping>            EntityIndices;
                std::map<VertexTopologies, RenderStage3D<IndexedDrawCommand>*>      IndexedStages;
                std::map<VertexTopologies, RenderStage3D<DrawCommand>*>             RenderStages;



                /** UTILITIES **/
                void Add(const IGeometric<Vector3>& entity);
                void CreateStage(VertexTopologies topology, bool isIndexed);
                void CreateLayer(VertexTopologies topology);

        };
    }
}
