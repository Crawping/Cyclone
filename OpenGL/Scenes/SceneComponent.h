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

                bool IsVisible()                                                    const override { return _isVisible; }
                /// <summary> Gets whether the component has any updates queued. </summary>
                bool NeedsUpdate()                                                  const override { return _needsUpdate; }

                const string& Name()                                                const override { return _name; }
                /// <summary> Gets the parent scene layer to which the component belongs. </summary>
                ISceneLayer& Parent()                                               const override { return _parent; }
                /// <summary> Gets the GPU configuration used to render the contents of the scene component. </summary>
                const GraphicsSettings& Settings()                                  const { return _settings; }

                
                OpenGLAPI SceneComponent& CullingMode(CullingModes value);
                OpenGLAPI SceneComponent& IsBlendEnabled(bool value);
                OpenGLAPI SceneComponent& IsDepthTestEnabled(bool value);
                OpenGLAPI SceneComponent& IsStencilTestEnabled(bool value);
                OpenGLAPI SceneComponent& IsVisible(bool value)                     override;
                OpenGLAPI SceneComponent& Pipeline(GraphicsPipeline* value);
                OpenGLAPI SceneComponent& Projection(ITransformation3D* value);
                /// <summary> Sets the GPU configuration used to render the contents of the scene component. </summary>
                OpenGLAPI SceneComponent& Settings(const GraphicsSettings& value)   override;
                OpenGLAPI SceneComponent& Target(FrameBuffer* value);
                OpenGLAPI SceneComponent& View(ITransformation3D* value);




                /** UTILITIES **/
                OpenGLAPI virtual bool Contains(const IRenderable<Vector3>& entity) const override;
                OpenGLAPI virtual void Insert(const IRenderable<Vector3>& entity)   override;
                OpenGLAPI virtual void Update()                                     override;

            protected:

                void NeedsUpdate(bool value) { _needsUpdate = _needsUpdate ? true : value; }


                OpenGLAPI SceneComponent(const string& name, ISceneLayer& parent);


                //OpenGLAPI ResourceMapping& Register(const IRenderable<Vector3>& entity)                   override;

            private:

                /** PROPERTY DATA **/
                bool                _isVisible;
                string              _name;
                bool                _needsUpdate;
                ISceneLayer&        _parent;
                GraphicsSettings    _settings;

                //BST<const IRenderable<Vector3>*, ResourceMapping> Entities;
                Set<const IRenderable<Vector3>*> Entities;

        };


    }
}
