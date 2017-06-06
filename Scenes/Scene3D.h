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
    namespace Scenes
    {

        class Scene3D : public SceneComponent3D
        {
            public:

                /** PROPERTIES **/
                //const Volume& Bounds()              const override { return Volume(); }
                //List<ISceneComponent*> Children()   const override { return { }; }
                const Entity3D* Model()             const override { return nullptr; }
                const Scene3D& Parent()             const override { return *this; }
                const Transform3D& Transform()      const override { return _transform; }



                /** CONSTRUCTOR **/
                SceneAPI Scene3D();



                /** UTILITIES **/
                //SceneAPI bool Contains(const ISceneComponent* child)    const override;
                //SceneAPI void Insert(ISceneComponent* child)            override;
                //SceneAPI bool Intersects(const LineSegment& line)       const override;
                //SceneAPI void Update()                                  override;
                //SceneAPI bool Contains(uint entity) const;
                //SceneAPI uint Insert(const IRenderable& entity);
                //SceneAPI void Remove(uint entity);
                //SceneAPI void Update() override;

                //SceneAPI void Set(uint entity, uint property);
                //SceneAPI void Set(const string& entity, const string& property);

            private:

                Transform3D _transform;
                //VirtualMemory   _memory;
                //VirtualMachine  _vm;

                //void CreateEntityClass();
                
        };

    }
}
