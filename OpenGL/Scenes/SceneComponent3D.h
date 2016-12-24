/* CHANGELOG
 * Written by Josh Grooms on 20161219
 */

#pragma once
#include "GraphicsSettings.h"
#include "Collections/BST.h"
#include "Collections/Set.h"
#include "Interfaces/IScene.h"



namespace Cyclone
{
    namespace OpenGL
    {

        class StageGroup3D;

        class SceneComponent3D : public virtual ISceneComponent
        {

            public:

                OpenGLAPI List<IRenderStage&> Stages()          const override;
                
                bool NeedsUpdate()                              const override { return _needsUpdate; }
                const GraphicsSettings& Settings()              const { return _settings; }


                OpenGLAPI SceneComponent3D& Settings(const GraphicsSettings& value);




                OpenGLAPI SceneComponent3D();
                OpenGLAPI ~SceneComponent3D();



                OpenGLAPI void Insert(const ResourceMapping& resource)  override;
                OpenGLAPI void ClearCommands();
                OpenGLAPI void ClearMappings();
                OpenGLAPI void Remove(const ResourceMapping& resource)  override;
                OpenGLAPI void Update()                                 override;

            private:

                bool                _isVisible;
                bool                _needsUpdate;
                GraphicsSettings    _settings;


                Set<const ResourceMapping*>             Resources;
                BST<VertexTopologies, StageGroup3D*>    Staging;

                StageGroup3D* CreateStage(VertexTopologies topology);
                
        };
    }
}
