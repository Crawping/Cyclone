/* CHANGELOG
 * Written by Josh Grooms on 20161219
 */

#pragma once
#include "Collections/BST.h"
#include "GraphicsSettings.h"
#include "Interfaces/IScene.h"
#include "Scenes/RenderStage3D.h"
#include "Scenes/SceneStage3D.h"
#include <set>



namespace Cyclone
{
    namespace OpenGL
    {
        struct BufferIndices;



        class SceneLayer3D : public virtual ISceneLayer
        {

            public:
                
                /** PROPERTIES **/
                //OpenGLAPI List<ISceneStage&> Stages()                   const override;
                virtual const string& Name()                            const override { return _name; }
                virtual bool NeedsUpdate()                              const override { return _needsUpdate; }

                SceneLayer3D& Name(const string& value)                 { _name = value; return *this; }



                /** CONSTRUCTOR **/
                OpenGLAPI SceneLayer3D(const string& name = "");
                virtual ~SceneLayer3D() { }



                /** UTILITIES **/
                OpenGLAPI void Add(const BufferIndices& indices);
                OpenGLAPI void Update() override;

            private:

                /** PROPERTY DATA **/
                bool                _isVisible;
                bool                _needsUpdate;
                string              _name;



                /** COLLECTIONS **/
                std::set<const BufferIndices*>      EntityIndices;
                BST<string, SceneStage3D*>           _stages;



        };
    }
}
