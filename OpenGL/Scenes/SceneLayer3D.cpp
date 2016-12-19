#include "Scenes/SceneLayer3D.h"
#include "Scenes/Scene3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/
        List<ISceneStage&> SceneLayer3D::Stages() const
        {
            return List<ISceneStage&>();
        }



        /** CONSTRUCTOR **/
        SceneLayer3D::SceneLayer3D(const string& name) :
            _name(name),
            _needsUpdate(false)
        {

        }



        void SceneLayer3D::Add(const BufferIndices& indices)
        {

        }
        void SceneLayer3D::Update()
        {

        }


    }
}