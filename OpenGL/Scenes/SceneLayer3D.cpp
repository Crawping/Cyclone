#include "Scenes/SceneLayer3D.h"
#include "Scenes/Scene3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/
        List<ISceneComponent&> SceneLayer3D::Components() const
        {
            List<ISceneComponent&> components;
            components.Append((ISceneComponent&)*this);

            for (auto& component : _components.Values())
                components.Append(component);

            return components;
        }
        List<IRenderStage&> SceneLayer3D::Stages() const
        {
            List<IRenderStage&> stages = SceneComponent3D::Stages();

            for (auto& stage : _components.Values())
                stages.Append(stage.Stages());

            return stages;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        SceneLayer3D::SceneLayer3D()
        {

        }



        /** UTILITIES **/
        void SceneLayer3D::Insert(const string& name, ISceneComponent& stage)
        {
            _components.Insert(name, stage);
        }
        void SceneLayer3D::Associate(const string& name, const ResourceMapping& resource)
        {
            if (!_components.Contains(name)) { return; }
            _components[name].Insert(resource);
        }
        void SceneLayer3D::Dissociate(const string& name, const ResourceMapping& resource)
        {
            if (!_components.Contains(name)) { return; }
            _components[name].Remove(resource);
        }
        void SceneLayer3D::Remove(const string& name)
        {
            _components.Remove(name);
        }
        void SceneLayer3D::Update()
        {
            SceneComponent3D::Update();
            for (auto& c : _components.Values())
                c.Update();
        }

    }
}