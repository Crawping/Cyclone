#include "Scene3D.h"
//#include "Execution/Shorthand.h"



namespace Cyclone
{
    namespace Scenes
    {

        /** PROPERTIES **/
        Scene3D& Scene3D::Transform(const Transform3D& value)
        {
            SceneComponent3D::Transform(value);
            
            return *this;
        }
        Scene3D& Scene3D::View(const Camera& value)
        {
            _view = value;
            _onViewUpdate(*this, value);
            return *this;
        }



        /** CONSTRUCTOR **/
        Scene3D::Scene3D()
            //SceneComponent3D(*this)
        {
            
        }



        /** EVENTS **/
        Scene3D::Listener<Scene3D, IComponent> Scene3D::OnComponentInsertion(Callback<Scene3D, IComponent> callback)
        {
            return _onComponentInsertion.Subscribe(callback);
        }
        Scene3D::Listener<Scene3D, IComponent> Scene3D::OnComponentRemoval(Callback<Scene3D, IComponent> callback)
        {
            return _onComponentRemoval.Subscribe(callback);
        }
        Scene3D::Listener<IComponent, Resource<IGeometric>> Scene3D::OnGeometryUpdate(Callback<IComponent, Resource<IGeometric>> callback)
        {
            return _onGeometryUpdate.Subscribe(callback);
        }
        Scene3D::Listener<IComponent, IMaterial> Scene3D::OnMaterialUpdate(Callback<IComponent, IMaterial> callback)
        {
            return _onMaterialUpdate.Subscribe(callback);
        }
        Scene3D::Listener<IComponent, ISpatialTransform> Scene3D::OnTransformUpdate(Callback<IComponent, ISpatialTransform> callback)
        {
            return _onTransformUpdate.Subscribe(callback);
        }
        Scene3D::Listener<Scene3D, Camera> Scene3D::OnViewUpdate(Callback<Scene3D, Camera> callback)
        {
            return _onViewUpdate.Subscribe(callback);
        }



        void Scene3D::ProcessTransformUpdate(const IComponent& src, const ISpatialTransform& evt)
        {
            if (&src == this) { return; }
            _onTransformUpdate(src, evt);
        }
    }
}