#include "Components/SceneComponent3D.h"



namespace Cyclone
{
    namespace Scenes
    {

        /** PROPERTIES **/
        SceneComponent3D& SceneComponent3D::Orientation(const Vector3& value)
        {
            _transform.Orientation(value);
            //_onTransformUpdate(*this, Transform());
            return *this;
        }
        SceneComponent3D& SceneComponent3D::Position(const Vector3& value)
        {
            _transform.Position(value);
            //_onTransformUpdate(*this, Transform());
            return *this;
        }
        SceneComponent3D& SceneComponent3D::Scale(const Vector3& value)
        {
            _transform.Scale(value);
            //_onTransformUpdate(*this, Transform());
            return *this;
        }
        SceneComponent3D& SceneComponent3D::Transform(const Transform3D& value)
        {
            _transform = value;
            //_onTransformUpdate(*this, value);
            return *this;
        }



        /** CONSTRUCTOR **/
        SceneComponent3D::SceneComponent3D()
            //SceneComponent(parent)
            //_isVisible(true),
            //_model(nullptr)
            //_parent(parent),
            //_tag("")
        {

        }



        /** UTILITIES **/
        /*bool SceneComponent3D::Contains(const Vector3& point)           const
        {
            return false;
        }
        bool SceneComponent3D::Contains(const IComponent& child)   const
        {
            return _children.Contains((IComponent* const) &child);
        }
        void SceneComponent3D::Insert(IComponent& child)
        {
            _children.Insert(&child);
        }
        bool SceneComponent3D::Intersects(const Vector<Vector3, 2>& line) const
        {
            return false;
        }
        void SceneComponent3D::Remove(const IComponent& child)
        {
            _children.Remove((IComponent* const) &child);
        }
        void SceneComponent3D::Update()
        {

        }
*/
        //Event<const IComponent&, const ISpatialTransform&> _onTransformUpdate;


        /** EVENTS **/




        void SceneComponent3D::UpdateBounds()
        {

        }

    }
}