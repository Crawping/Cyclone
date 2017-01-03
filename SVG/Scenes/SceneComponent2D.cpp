#include "Scenes/SceneComponent2D.h"
#include "Scenes/Scene3D.h"



namespace Cyclone
{
    namespace SVG
    {

        List<IRenderStage&> SceneComponent2D::Stages() const
        {
            List<IRenderStage&> stages;
            for (auto& s : _stages)
                stages.Append(s);

            return stages;
        }



        SceneComponent2D::SceneComponent2D(const string& name, ISceneLayer& parent) :
            SceneComponent(name, parent)
        {
            _stages.Append(RenderStage2D());
        }



        void SceneComponent2D::Insert(const IRenderable& entity)
        {
            const IRenderable2D* entity2D = dynamic_cast<const IRenderable2D*>(&entity);
            if (!entity2D) { return; }

            ResourceMapping& map = SceneComponent::Register(entity);
            for (auto& s : _stages)
                s.Insert(map.EntityKey.Index(), *entity2D);
        }
        void SceneComponent2D::Remove(const IRenderable& entity)
        {
            if (!Contains(entity)) { return; }
            SceneComponent::Remove(entity);
            for (auto& s : _stages)
                s.Remove(dynamic_cast<const IRenderable2D&>(entity));
        }
        void SceneComponent2D::Remove(uint index)
        {
            _stages.Remove(index);
        }
        void SceneComponent2D::Update()
        {
            _stages.First().Settings(Settings());
            for (auto& s : _stages)
                s.Update();
        }
        void SceneComponent2D::Update(const IRenderable& entity)
        {
            Parent().Update(entity);
            const IRenderable2D* entity2D = dynamic_cast<const IRenderable2D*>(&entity);
            if (entity2D)
                entity2D->Update();
        }

    }
}