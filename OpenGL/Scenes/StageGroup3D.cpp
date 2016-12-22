#include "Scenes/StageGroup3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        List<IRenderStage&> StageGroup3D::Stages() const
        {
            return List<IRenderStage&>();
        }

        StageGroup3D& StageGroup3D::Name(const string& value)
        {
            _name = value;
            return *this;
        }
        StageGroup3D& StageGroup3D::Settings(const GraphicsSettings& value)
        {
            _settings = value;
            for (auto* s : _stages.Values())
                s->Settings(value);

            return *this;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        StageGroup3D::StageGroup3D(const string& name) : 
            _isVisible(true),
            _name(name)
        {

        }
        StageGroup3D::~StageGroup3D()
        {
            for (auto* s : _stages.Values())
                delete s;
        }



        /** UTILITIES **/
        void StageGroup3D::Add(VertexTopologies topology, const BufferIndices& indices)
        {
            SceneStage3D* stage = _stages.Contains(topology) ?
                _stages[topology] : new SceneStage3D(Name());

            stage->Add(indices);
        }
        void StageGroup3D::Remove(VertexTopologies topology, const BufferIndices& indices)
        {
            _stages[topology]->Remove(indices);
        }
        void StageGroup3D::Update()
        {
            for (auto* s : _stages.Values())
                s->Update();
        }

    }
}