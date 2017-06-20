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
            _onTransformUpdate(*this, value);
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
        Subscription<const Scene3D&, const IComponent&>
            Scene3D::OnComponentInsertion(const ICallback<void, const Scene3D&, const IComponent&>& callback)
        {
            return _onComponentInsertion.Subscribe(callback);
        }
        Subscription<const Scene3D&, const IComponent&>
            Scene3D::OnComponentRemoval(const ICallback<void, const Scene3D&, const IComponent&>& callback)
        {
            return _onComponentRemoval.Subscribe(callback);
        }
        Subscription<const Scene3D&, Resource<IGeometric>>
            Scene3D::OnGeometryUpdate(const ICallback<void, const Scene3D&, Resource<IGeometric>>& callback)
        {
            return _onGeometryUpdate.Subscribe(callback);
        }

        Subscription<const Scene3D&, const Camera&>
            Scene3D::OnViewUpdate(const ICallback<void, const Scene3D&, const Camera&>& callback)
        {
            return _onViewUpdate.Subscribe(callback);
        }

    }
}