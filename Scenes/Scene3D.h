/* CHANGELOG
 * Written by Josh Grooms on 20170203
 */

#pragma once
#include "SceneAPI.h"
//#include "VirtualMachine.h"
#include "Components/SceneComponent3D.h"
#include "Interfaces/IRenderable.h"
#include "Interfaces/IScene.h"
//#include "Interfaces/ISceneComponent.h"



namespace Cyclone
{
    namespace 
    { 
        using namespace OpenGL;
        //using namespace VM;
    }

    namespace Scenes
    {

        class Scene3D : public SceneComponent3D
        {
            public:

                /** CONSTRUCTOR **/
                SceneAPI Scene3D();

                //SceneAPI bool Contains(uint entity) const;
                //SceneAPI uint Insert(const IRenderable& entity);
                //SceneAPI void Remove(uint entity);
                //SceneAPI void Update() override;

                //SceneAPI void Set(uint entity, uint property);
                //SceneAPI void Set(const string& entity, const string& property);

            private:

                //VirtualMemory   _memory;
                //VirtualMachine  _vm;

                void CreateEntityClass();
                
        };

    }
}
