#include "Scene3D.h"
//#include "Execution/Shorthand.h"



namespace Cyclone
{
    namespace Scenes
    {

        /** PROPERTIES **/
        Scene3D& Scene3D::Transform(const Transform3D& value)
        {
            _transform = value;

            return *this;
        }
        Scene3D& Scene3D::View(const Camera& value)
        {
            _view = value;
            OnViewUpdate(*this, View());
            return *this;
        }


        Scene3D::Scene3D(): 
            SceneComponent3D(*this)
        {
            
        }

    }
}