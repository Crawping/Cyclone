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

    }
}