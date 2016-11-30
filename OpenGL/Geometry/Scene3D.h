/* CHANGELOG
 * Written by Josh Grooms on 20160724
 */

#pragma once
#include "GraphicsSettings.h"
#include "RenderStage3D.h"
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

#include <map>



namespace Cyclone
{
    namespace OpenGL
    {
        class IRenderStage;


        /// <summary> A 3D scene representing a collection of renderable objects. </summary>
        class Scene3D : public IRenderableScene
        {

            public:

                OpenGLAPI List<IRenderStage*> Stages() const override;

                Scene3D& IsBlendEnabled(bool value)             { _settings.IsBlendEnabled = value; return *this; }
                Scene3D& IsDepthTestEnabled(bool value)         { _settings.IsDepthTestEnabled = value; return *this; }
                Scene3D& IsStencilTestEnabled(bool value)       { _settings.IsStencilTestEnabled = value; return *this; }
                Scene3D& IsVisible(bool value)                  { _isVisible = value; return *this; }

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
                OpenGLAPI void Add(const IRenderable3D<Vertex::Standard>& entity);
                OpenGLAPI void Remove(const IRenderable3D<Vertex::Standard>& entity);
                OpenGLAPI void Update();
                OpenGLAPI void Update(const IRenderable3D<Vertex::Standard>& entity);

                OpenGLAPI void Add(const string& stage, const IRenderable3D<Vertex::Standard>& entity);
                OpenGLAPI void CreateStage(const string& name);
                OpenGLAPI void Settings(const string& stage, const GraphicsSettings& value);


            private:

                struct BufferIndices
                {
                    uint EntityIndex;
                    uint IndicesCount;
                    uint IndicesIndex;
                    RegistryKey<MaterialData> MaterialIndex;
                    RegistryKey<TransformData> TransformIndex;
                    uint VertexCount;
                    uint VertexIndex;
                };



                /** PROPERTY DATA **/
                bool                _isVisible;
                GraphicsSettings    _settings;



                /** BUFFERED DATA **/
                UniformBuffer<EntityData>           Entities;
                IndexBuffer                         Indices;
                ResourceLibrary<MaterialData>       Materials;
                ResourceLibrary<TransformData>      Transforms;
                VertexBuffer<Vertex::Standard>      Vertices;



                /** BUFFER & STAGE MAPPINGS **/
                std::map<const IRenderable3D<Vertex::Standard>*, BufferIndices>     EntityIndices;
                std::map<VertexTopologies, RenderStage3D<IndexedDrawCommand>*>      IndexedStages;
                std::map<VertexTopologies, RenderStage3D<DrawCommand>*>             RenderStages;



                /** UTILITIES **/
                RegistryKey<TransformData> Add(const IGeometric3D<Vertex::Standard>& entity);
                RegistryKey<MaterialData> Add(const IMaterialEntity& entity);
                void CreateStage(VertexTopologies topology, bool isIndexed);

        };
    }
}
