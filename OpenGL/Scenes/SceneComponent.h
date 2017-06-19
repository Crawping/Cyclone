/* CHANGELOG
 * Written by Josh Grooms on 20161224
 */

#pragma once
#include "GraphicsSettings.h"
#include "Collections/BST.h"
#include "Collections/Set.h"
#include "Interfaces/IGraphicsBuffer.h"
#include "Interfaces/IScene.h"
#include "Interfaces/ISpatialTransform.h"



namespace Cyclone
{
    namespace OpenGL
    {

        class SceneComponent : public virtual ISceneComponent
        {

            public:

                /** PROPERTIES **/
                virtual CullingModes CullingMode()                                  const { return _settings.CullingMode; }
                virtual bool IsBlendEnabled()                                       const { return _settings.IsBlendEnabled; }
                virtual bool IsDepthTestEnabled()                                   const { return _settings.IsDepthTestEnabled; }
                virtual bool IsStencilTestEnabled()                                 const { return _settings.IsStencilTestEnabled; }
                virtual bool IsVisible()                                            const override { return _isVisible; }
                /// <summary> Gets whether the component has any updates queued. </summary>
                virtual bool NeedsUpdate()                                          const override { return _needsUpdate; }

                virtual const string& Name()                                        const override { return _name; }
                /// <summary> Gets the parent scene layer to which the component belongs. </summary>
                virtual ISceneLayer& Parent()                                       const override { return _parent; }
                virtual const IGraphicsPipeline* Pipeline()                         const { return _settings.Pipeline; }
                virtual const ISpatialTransform* Projection()                       const { return _settings.Projection; }
                /// <summary> Gets the GPU configuration used to render the contents of the scene component. </summary>
                virtual const GraphicsSettings& Settings()                          const { return _settings; }
                virtual const FrameBuffer* Target()                                 const { return _settings.Target; }
                virtual const ISpatialTransform* View()                             const { return _settings.View; }


                OpenGLAPI virtual SceneComponent& CullingMode(CullingModes value);
                OpenGLAPI virtual SceneComponent& IsBlendEnabled(bool value);
                OpenGLAPI virtual SceneComponent& IsDepthTestEnabled(bool value);
                OpenGLAPI virtual SceneComponent& IsStencilTestEnabled(bool value);
                OpenGLAPI virtual SceneComponent& IsVisible(bool value)                     override;
                OpenGLAPI virtual SceneComponent& Pipeline(IGraphicsPipeline* value);
                OpenGLAPI virtual SceneComponent& Projection(ISpatialTransform* value);
                /// <summary> Sets the GPU configuration used to render the contents of the scene component. </summary>
                OpenGLAPI virtual SceneComponent& Settings(const GraphicsSettings& value)   override;
                OpenGLAPI virtual SceneComponent& Target(FrameBuffer* value);
                OpenGLAPI virtual SceneComponent& View(ISpatialTransform* value);



                /** UTILITIES **/
                OpenGLAPI virtual void Update() override;

            protected:

                OpenGLAPI SceneComponent(const string& name, ISceneLayer& parent);

            private:

                /** PROPERTY DATA **/
                bool                _isVisible;
                string              _name;
                bool                _needsUpdate;
                ISceneLayer&        _parent;
                GraphicsSettings    _settings;

        };


    }
}
