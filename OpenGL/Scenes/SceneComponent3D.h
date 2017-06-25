/* CHANGELOG
 * Written by Josh Grooms on 20161219
 */

#pragma once
#include "Buffers/GeometryBuffer.h"
#include "Buffers/UniformMap.h"
#include "Buffers/UniformData.h"
#include "Collections/BST.h"
#include "Collections/Set.h"
#include "Resources/Resource.h"
#include "Scenes/SceneComponent.h"



namespace Cyclone
{
    namespace OpenGL
    {

        struct StageGroup3D;

        class SceneComponent3D : public SceneComponent
        {

            public:

                /** PROPERTIES **/
                OpenGLAPI List<BufferBinding> Buffers()                 const override;
                /// <summary> Gets a list of all rendering stages that must be executed to display the scene component. </summary>
                OpenGLAPI List<IRenderStage&> Stages()                  const override;



                /** CONSTRUCTOR & DESTRUCTOR **/
                OpenGLAPI SceneComponent3D(const string& name, ISceneLayer& parent);
                OpenGLAPI ~SceneComponent3D();



                /** UTILITIES **/
                OpenGLAPI void Insert(const Resource<IRenderable>& entity)  override;
                OpenGLAPI void Update()                                     override;
                OpenGLAPI void Update(const Resource<IRenderable>& entity)  override;

            protected:

                OpenGLAPI void UpdateGeometry(const Resource<IRenderable>& entity);

            private:

                bool NeedsUpdate;

                /** COLLECTIONS **/
                BST<PointTopologies, StageGroup3D*>     Staging;

                GeometryBuffer<Vertex>                  _geometry;
                UniformMap<uint, EntityData>            _resources;
                BST<uint, Resource<IRenderable>>        _entities;



                /** UTILITIES **/
                void ClearCommands();
                StageGroup3D* CreateStage(PointTopologies topology);

        };
    }
}
