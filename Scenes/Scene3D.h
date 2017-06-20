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
                SceneAPI Subscription<const Scene3D&, const IComponent&>
                    OnComponentInsertion(const ICallback<void, const Scene3D&, const IComponent&>& callback);
                SceneAPI Subscription<const Scene3D&, const IComponent&>
                    OnComponentRemoval(const ICallback<void, const Scene3D&, const IComponent&>& callback);
                SceneAPI Subscription<const Scene3D&, Resource<IGeometric>>
                    OnGeometryUpdate(const ICallback<void, const Scene3D&, Resource<IGeometric>>& callback);
                //SceneAPI Subscription<const Scene3D&, const Transform3D&>
                //    OnTransformUpdate(const ICallback<void, const Scene3D&, const Transform3D&>& callback);
                SceneAPI Subscription<const Scene3D&, const Camera&>
                    OnViewUpdate(const ICallback<void, const Scene3D&, const Camera&>& callback);

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

            private:

                //Transform3D     _transform;
                Camera          _view;

                using S3D = const Scene3D&;
                Event<S3D, const IComponent&>       _onComponentInsertion;
                Event<S3D, const IComponent&>       _onComponentRemoval;
                Event<S3D, Resource<IGeometric>>    _onGeometryUpdate;
                Event<S3D, const Transform3D&>      _onTransformUpdate;
                Event<S3D, const Camera&>           _onViewUpdate;


                //VirtualMemory   _memory;
                //VirtualMachine  _vm;

                //void CreateEntityClass();
                
        };

    }
}
