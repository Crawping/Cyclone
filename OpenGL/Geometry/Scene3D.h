/* CHANGELOG
 * Written by Josh Grooms on 20160724
 */

#pragma once
#include "RenderStage.h"
#include "Buffers/DrawBuffer.h"
#include "Buffers/UniformData.h"
#include "GL/OpenGLAPI.h"
#include "Interfaces/IRenderable.h"
//#include "Interfaces/IRenderingStage.h"
#include "Interfaces/IUpdatable.h"
#include <map>
#include <set>



namespace Cyclone
{
    namespace OpenGL
    {

        /// <summary> A 3D scene representing a collection of renderable objects. </summary>
        class Scene3D
        {

            public:

                OpenGLAPI List<IRenderingStage3D*> Stages() const;


                /** CONSTRUCTOR **/
                /// <summary> Constructs an empty scene object that can be populated with renderable entities. </summary>
                OpenGLAPI Scene3D();



                /** UTILITIES **/
                OpenGLAPI void Add(const IRenderable2D<float>& entity);
                /// <summary> Adds a renderable entity to this scene. </summary>
                /// <param name="entity">
                ///     A reference to the renderable entity that will be added to the scene. If this entity already exists
                ///     within this collection (i.e. it has been added previously), then its corresponding data store will
                ///     be updated. Otherwise, this method generates a new entry in the scene's data collection to hold the
                ///     necessary rendering information for the entity.
                /// </param>
                OpenGLAPI void Add(const IRenderable3D<Vertex::Standard>& entity);
                OpenGLAPI void Remove(const IRenderable2D<float>& entity);
                OpenGLAPI void Remove(const IRenderable3D<Vertex::Standard>& entity);
                OpenGLAPI void Render(GPU* gpu) const;
                OpenGLAPI void Update();
                OpenGLAPI void Update(const IRenderable3D<Vertex::Standard>& entity);

            private:

                std::map<VertexTopologies, DrawBuffer<DrawCommand>>             Buffers;
                std::map<VertexTopologies, DrawBuffer<IndexedDrawCommand>>      IndexedBuffers;

                std::set<const IRenderable2D<float>*>                           PathBuffer;

                std::map<VertexTopologies, IRenderingStage3D*>                  Stages3D;
                //std::map<VertexTopologies, IRenderingStage2D*>

                //List<IRenderingStage3D*> RenderingStages;
                //RenderStage3D                                                   

        };
    }
}
