/* CHANGELOG
 * Written by Josh Grooms on 20170203
 */

#pragma once
#include "SceneAPI.h"
//#include "VirtualMachine.h"
#include "Components/SceneComponent3D.h"
#include "IO/Event.h"
#include "Interfaces/IRenderable.h"
#include "Spatial/Camera.h"
//#include "Interfaces/IComponent.h"



namespace Cyclone
{
    namespace Scenes
    {
        class Scene3D: public SceneComponent3D
        {
            public:

                /** ALIASES **/
                template<typename T, typename U>
                using Callback = const ICallback<void, const T&, const U&>&;

                template<typename T, typename U>
                using Listener = Subscription<const T&, const U&>;



                /** PROPERTIES **/
                //using SceneComponent3D::Transform;
                //const Scene3D& Parent()                         const override { return *this; }
                const Transform3D& Transform()                  const override { return SceneComponent3D::Transform(); }
                const Camera& View()                            const { return _view; }

                SceneAPI Scene3D& Transform(const Transform3D& value);
                SceneAPI Scene3D& View(const Camera& value);

                //using SceneComponent3D::Transform;
                //using Scene3D::Transform;



                /** EVENTS **/


                /** CONSTRUCTOR **/
                SceneAPI Scene3D();



                /** UTILITIES **/



                /** EVENTS **/
                SceneAPI Listener<Scene3D, IComponent>                  OnComponentInsertion(Callback<Scene3D, IComponent> callback);
                SceneAPI Listener<Scene3D, IComponent>                  OnComponentRemoval(Callback<Scene3D, IComponent> callback);
                SceneAPI Listener<IComponent, Resource<IGeometric>>     OnGeometryUpdate(Callback<IComponent, Resource<IGeometric>> callback);
                SceneAPI Listener<IComponent, IMaterial>                OnMaterialUpdate(Callback<IComponent, IMaterial> callback);
                SceneAPI Listener<IComponent, ISpatialTransform>        OnTransformUpdate(Callback<IComponent, ISpatialTransform> callback);
                SceneAPI Listener<Scene3D, Camera>                      OnViewUpdate(Callback<Scene3D, Camera> callback);

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

            protected:

                //void ProcessComponentInsertion()
                //{

                //}
                //void ProcessGeometryUpdate()
                //{

                //}
                //void ProcessViewUpdate()
                //{

                //}
                SceneAPI void ProcessTransformUpdate(const IComponent& src, const ISpatialTransform& evt) override;

            private:

                //Transform3D     _transform;
                Camera          _view;

                Event<const Scene3D&, const IComponent&>                _onComponentInsertion;
                Event<const Scene3D&, const IComponent&>                _onComponentRemoval;
                Event<const IComponent&, const Resource<IGeometric>&>   _onGeometryUpdate;
                Event<const IComponent&, const IMaterial&>              _onMaterialUpdate;
                Event<const IComponent&, const ISpatialTransform&>      _onTransformUpdate;
                Event<const Scene3D&, const Camera&>                    _onViewUpdate;


                //VirtualMemory   _memory;
                //VirtualMachine  _vm;

                //void CreateEntityClass();
                
        };

    }
}
