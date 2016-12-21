/* CHANGELOG
 * Written by Josh Grooms on 20161219
 */

#pragma once
#include "GraphicsSettings.h"
#include "Collections/BST.h"
#include "Interfaces/IGraphicsBuffer.h"
#include "Interfaces/IScene.h"
#include "Scenes/SceneStage3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        class SceneComponent : public virtual ISceneComponent
        {
            public:
                
                virtual const string& Name()                        const override { return _name; }

                virtual SceneComponent& Name(const string& value)   { _name = value; return *this; }


            private:

                string _name;

        };


        class SceneComponent3D : public virtual SceneComponent
        {

            public:


            private:

                BST<string, SceneStage3D> _stages;
        };
    }
}
