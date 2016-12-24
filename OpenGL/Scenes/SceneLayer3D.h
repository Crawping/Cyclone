/* CHANGELOG
 * Written by Josh Grooms on 20161219
 */

#pragma once
#include "Collections/BST.h"
#include "GraphicsSettings.h"
#include "Interfaces/IScene.h"
#include "Pipelines/RenderStage3D.h"
#include "Scenes/SceneComponent3D.h"




namespace Cyclone
{
    namespace OpenGL
    {
        struct ResourceMapping;



        class SceneLayer3D : 
            public SceneComponent3D,
            public virtual ISceneLayer
        {

            public:
                
                /** PROPERTIES **/
                OpenGLAPI List<ISceneComponent&> Components()           const override;
                OpenGLAPI List<IRenderStage&> Stages()                  const override;

                virtual bool NeedsUpdate()                              const override { return _needsUpdate; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                OpenGLAPI SceneLayer3D();
                virtual ~SceneLayer3D() { }



                /** UTILITIES **/
                OpenGLAPI void Insert(const string& name, ISceneComponent& stage)               override;
                OpenGLAPI void Associate(const string& name, const ResourceMapping& resource)   override;
                OpenGLAPI void Dissociate(const string& name, const ResourceMapping& resource)  override;
                OpenGLAPI void Remove(const string& name)                                       override;
                OpenGLAPI void Update()                                                         override;

            private:

                /** PROPERTY DATA **/
                bool                _isVisible;
                bool                _needsUpdate;



                /** COLLECTIONS **/
                BST<string, ISceneComponent&> _components;



        };
    }
}
