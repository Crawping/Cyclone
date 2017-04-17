#include "Components/SceneComponent3D.h"



namespace Cyclone
{
    namespace Scenes
    {

        /** PROPERTIES **/
        SceneComponent3D& SceneComponent3D::IsVisible(bool value)
        {
            _isVisible = value;
            return *this;
        }
        SceneComponent3D& SceneComponent3D::Model(IRenderable* value)
        {
            _model = value;
            return *this;
        }
        SceneComponent3D& SceneComponent3D::Parent(ISceneComponent& value)
        {
            _parent = value;
            return *this;
        }
        SceneComponent3D& SceneComponent3D::Transformation(const Transform& value)
        {
            _transformation = value;
            return *this;
        }



        /** CONSTRUCTOR **/
        SceneComponent3D::SceneComponent3D(ISceneComponent& parent) :
            _isVisible(true),
            _model(nullptr),
            _parent(parent),
            _tag("")
        {

        }



        /** UTILITIES **/
        bool SceneComponent3D::Contains(const Vector3& point)           const
        {
            return false;
        }
        bool SceneComponent3D::Contains(const ISceneComponent& child)   const
        {
            return false;
        }
        void SceneComponent3D::Insert(ISceneComponent& child)
        {

        }
        bool SceneComponent3D::Intersects(const Vector<Vector3, 2>& line) const
        {
            return false;
        }
        void SceneComponent3D::Remove(const ISceneComponent& child)
        {

        }
        void SceneComponent3D::Update()
        {

        }


    }
}