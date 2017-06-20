/* CHANGELOG
 * Written by Josh Grooms on 20170203
 */

#pragma once
#include "SceneAPI.h"
//#include "VirtualMachine.h"
#include "Components/SceneComponent3D.h"
#include "IO/Event.h"
#include "Interfaces/IRenderable.h"
#include "Interfaces/IScene.h"
#include "Resources/ResourceLibrary2.h"
#include "Spatial/Camera.h"
//#include "Interfaces/ISceneComponent.h"



namespace Cyclone
{
    namespace Scenes
    {
        class Scene3D : public SceneComponent3D
        {
            public:

                /** PROPERTIES **/
                const Scene3D& Parent()                         const override { return *this; }
                const Transform3D& Transform()                  const override { return _transform; }
                const Camera& View()                            const { return _view; }

                SceneAPI Scene3D& Transform(const Transform3D& value);
                SceneAPI Scene3D& View(const Camera& value);



                /** EVENTS **/
                Event<const Scene3D&, const ISceneComponent&>   OnComponentInsertion;
                Event<const Scene3D&, const ISceneComponent&>   OnComponentRemoval;
                Event<const Scene3D&, const Transform3D&>       OnTransformUpdate;
                Event<const Scene3D&, const Camera&>            OnViewUpdate;
                //Event<const Camera&> OnCameraMotion;
                //Event<const Camera&> OnCameraOrientation;



                /** CONSTRUCTOR **/
                SceneAPI Scene3D();



                /** UTILITIES **/
                //template<typename T> Resource<T> Create(const string& name)
                //{
                //    return Resources.Create<T>(name);
                //}
                //template<typename T, typename ... U>
                //Resource<T> Create(const string& name, const ICallback<T, U...>& constructor, U ... arguments)
                //{
                //    return Resources.Create<T, U...>(name, constructor, arguments...);
                //}
                //template<typename T> void Destroy(Resource<T> value)
                //{
                //    
                //}



                //SceneAPI bool Contains(const ISceneComponent* child)    const override;
                //SceneAPI void Insert(ISceneComponent* child)            override;
                //SceneAPI bool Intersects(const LineSegment3D& line)       const override;
                //SceneAPI void Update()                                  override;
                //SceneAPI bool Contains(uint entity) const;
                //SceneAPI uint Insert(const IRenderable& entity);
                //SceneAPI void Remove(uint entity);
                //SceneAPI void Update() override;

                //SceneAPI void Set(uint entity, uint property);
                //SceneAPI void Set(const string& entity, const string& property);

            protected:

                void ProcessViewUpdate()
                {

                }

            private:

                Transform3D     _transform;
                Camera          _view;

                ResourceLibrary2 Resources;
                //VirtualMemory   _memory;
                //VirtualMachine  _vm;

                //void CreateEntityClass();
                
        };

    }
}
