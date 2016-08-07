/* CHANGELOG
 * Written by Josh Grooms on 20160724
 */

#pragma once
#include "Buffers/CommandBuffer.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/UniformData.h"
#include "Buffers/VertexBuffer.h"
#include "GL/OpenGLAPI.h"
#include <map>



namespace Cyclone
{
    namespace OpenGL
    {
        class IRenderableEntity;

        /// <summary> A 3D scene representing a collection of renderable objects. </summary>
        class Scene3D
        {

            public:
                            
                /** CONSTRUCTOR **/
                /// <summary> Constructs an empty scene object that can be populated with renderable entities. </summary>
                OpenGLAPI Scene3D();



                /** UTILITIES **/
                /// <summary> Adds a renderable entity to this scene. </summary>
                /// <param name="entity"> 
                ///     A reference to the renderable entity that will be added to the scene. If this entity already exists 
                ///     within this collection (i.e. it has been added previously), then its corresponding data store will 
                ///     be updated. Otherwise, this method generates a new entry in the scene's data collection to hold the 
                ///     necessary rendering information for the entity.
                /// </param>
                OpenGLAPI void Add(const IRenderableEntity& entity);

                OpenGLAPI void Update();

                OpenGLAPI void Bind(int slot = 0) const;

            private:
                CommandBuffer               Commands;
                UniformBuffer<PerEntity>    Entities;
                VertexBuffer                Vertices;
                
                std::map<const IRenderableEntity*, uint> EntityIndices;
        };
    }
}