#include "Collections/List.h"
#include "Interfaces/IMaterial.h"
#include "Interfaces/IRenderable.h"
#include "Pipelines/RenderStage3D.h"
#include "Scenes/Scene3D.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {


        /** CONSTRUCTOR **/
        Scene3D::Scene3D(const string& name) :
            SceneLayer3D(name, *this)
        {

        }
        Scene3D::~Scene3D()
        {

        }
        
    }
}
