/* CHANGELOG
 * Written by Josh Grooms on 20161224
 */

#pragma once
#include "GraphicsSettings.h"
#include "Collections/BST.h"
#include "Collections/Set.h"
#include "Interfaces/IScene.h"
#include "Interfaces/IGraphicsBuffer.h"



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
                virtual const GraphicsPipeline* Pipeline()                          const { return _settings.Pipeline; }
                virtual const ITransformation3D* Projection()                       const { return _settings.Projection; }
                /// <summary> Gets the GPU configuration used to render the contents of the scene component. </summary>
                virtual const GraphicsSettings& Settings()                          const { return _settings; }
                virtual const FrameBuffer* Target()                                 const { return _settings.Target; }
                virtual const ITransformation3D* View()                             const { return _settings.View; }

                
                OpenGLAPI virtual SceneComponent& CullingMode(CullingModes value);
                OpenGLAPI virtual SceneComponent& IsBlendEnabled(bool value);
                OpenGLAPI virtual SceneComponent& IsDepthTestEnabled(bool value);
                OpenGLAPI virtual SceneComponent& IsStencilTestEnabled(bool value);
                OpenGLAPI virtual SceneComponent& IsVisible(bool value)                     override;
                OpenGLAPI virtual SceneComponent& Pipeline(GraphicsPipeline* value);
                OpenGLAPI virtual SceneComponent& Projection(ITransformation3D* value);
                /// <summary> Sets the GPU configuration used to render the contents of the scene component. </summary>
                OpenGLAPI virtual SceneComponent& Settings(const GraphicsSettings& value)   override;
                OpenGLAPI virtual SceneComponent& Target(FrameBuffer* value);
                OpenGLAPI virtual SceneComponent& View(ITransformation3D* value);



                /** UTILITIES **/
                OpenGLAPI virtual bool Contains(const IRenderable& entity)          const override;
                OpenGLAPI virtual void Insert(const IRenderable& entity)            override;
                OpenGLAPI virtual void Update()                                     override;

            protected:

                void NeedsUpdate(bool value) { _needsUpdate = _needsUpdate ? true : value; }


                OpenGLAPI SceneComponent(const string& name, ISceneLayer& parent);

            private:

                /** PROPERTY DATA **/
                bool                _isVisible;
                string              _name;
                bool                _needsUpdate;
                ISceneLayer&        _parent;
                GraphicsSettings    _settings;

                //BST<const IRenderable<Vector3>*, ResourceMapping> Entities;
                Set<const IRenderable*> Entities;

        };


    }
}
