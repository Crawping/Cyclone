/* CHANGELOG
 * Written by Josh Grooms on 20161219
 */

#pragma once
#include "Collections/BST.h"
#include "Collections/Set.h"
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
                /// <summary> Gets a list of all rendering stages that must be executed to display the scene component. </summary>
                OpenGLAPI List<IRenderStage&> Stages()                  const override;



                /** CONSTRUCTOR & DESTRUCTOR **/
                OpenGLAPI SceneComponent3D(const string& name, ISceneLayer& parent);
                OpenGLAPI ~SceneComponent3D();



                /** UTILITIES **/
                OpenGLAPI bool Contains(const IRenderable& entity)      const override;
                OpenGLAPI void Insert(const IRenderable& entity)        override;
                OpenGLAPI void Remove(const IRenderable& entity)        override;
                OpenGLAPI void Update()                                 override;
                OpenGLAPI void Update(const IRenderable& entity)        override;

            private:

                bool NeedsUpdate;

                /** COLLECTIONS **/
                BST<const IRenderable*, const ResourceMapping*>     Resources;
                BST<VertexTopologies, StageGroup3D*>                Staging;



                /** UTILITIES **/
                void ClearCommands();
                void ClearMappings();
                StageGroup3D* CreateStage(VertexTopologies topology);
                
        };
    }
}
