/* CHANGELOG
 * Written by Josh Grooms on 20160724
 */

#pragma once
#include "GraphicsSettings.h"
#include "Buffers/DrawBuffer.h"
#include "Buffers/UniformData.h"
#include "Collections/List.h"
#include "GL/OpenGLAPI.h"
#include "Interfaces/IRenderable.h"
#include "Interfaces/IUpdatable.h"

#include <map>
#include <set>



namespace Cyclone
{
    namespace OpenGL
    {
        class IRenderStage;


        /// <summary> A 3D scene representing a collection of renderable objects. </summary>
        class Scene3D : public IRenderableScene
        {

            public:

                OpenGLAPI const List<IRenderStage*>& Stages() const override;

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

            private:

                GraphicsSettings _settings;

                std::map<VertexTopologies, DrawBuffer<DrawCommand>>             Buffers;

                std::map<VertexTopologies, DrawBuffer<IndexedDrawCommand>>      IndexedBuffers;

                List<IRenderStage*>                                             Stages3D;                                              

        };
    }
}
