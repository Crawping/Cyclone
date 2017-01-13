#include "Scenes/SceneComponent2D.h"
#include "Scenes/Scene3D.h"



namespace Cyclone
{
    namespace SVG
    {

        /** INTERNAL FUNCTIONS **/
        const IRenderable2D* Downcast(const IRenderable& entity)
        {
            return dynamic_cast<const IRenderable2D*>(&entity);
        }

        struct SceneComponent2D::ComponentData
        {
            Set<const IRenderable2D*>   Components;
            ResourceMapping&            Map;

            ComponentData(ResourceMapping& map) : Map(map) { }
        };



        /** PROPERTIES **/
        List<IRenderStage&> SceneComponent2D::Stages() const
        {
            List<IRenderStage&> stages;
            stages.Append((IRenderStage&)_stage);
            return stages;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        SceneComponent2D::SceneComponent2D(const string& name, ISceneLayer& parent) :
            SceneComponent(name, parent),
            _needsUpdate(false)
        {
            
        }
        SceneComponent2D::~SceneComponent2D()
        {
            for (auto* c : Resources.Values())
                delete c;
        }



        /** UTILITIES **/
        bool SceneComponent2D::Contains(const IRenderable& entity) const
        {
            const IRenderable2D* entity2D = Downcast(entity);
            return entity2D ? Resources.Contains(entity2D) : false;
        }
        void SceneComponent2D::Insert(const IRenderable& entity)
        {
            const IRenderable2D* entity2D = Downcast(entity);
            if (!entity2D) { return; }

            ComponentData* data = Resources.Contains(entity2D) ?
                Resources[entity2D] : new ComponentData(Parent().Register(entity));
            
            Resources.Insert(entity2D, data);

            for (auto& c : entity2D->Components())
            {
                Insert(c);
                if (auto* c2d = Downcast(c))
                    data->Components.Insert(c2d);
            }

            _needsUpdate = true;
        }
        void SceneComponent2D::Remove(const IRenderable& entity)
        {
            const IRenderable2D* entity2D = Downcast(entity);
            if (!Resources.Contains(entity2D)) { return; }

            //Parent().Remove()
            ComponentData* data = Resources[entity2D];
            for (auto* c : data->Components)
                Remove(*c);

            delete Resources[entity2D];
            Resources.Remove(entity2D);

            _stage.Remove(*entity2D);
            _needsUpdate = true;
        }
        void SceneComponent2D::Update()
        {
            if (SceneComponent::NeedsUpdate())
            {
                SceneComponent::Update();
                _stage.Settings(Settings());
            }

            if (!_needsUpdate) { return; }

            _stage.ClearEntities();
            for (auto& kvp : Resources)
                _stage.Insert(kvp.Value->Map.EntityKey.Index(), (const IRenderable2D&) *(kvp.Key));

            _needsUpdate = false;
        }
        void SceneComponent2D::Update(const IRenderable& entity)
        {
            Parent().Update(entity);
            const IRenderable2D* entity2D = Downcast(entity);
            if ( !(entity2D && Resources.Contains(entity2D)) ) 
                return;

            entity2D->Update();
            ComponentData* data = Resources[entity2D];
            for (const auto& cmp : entity2D->Components())
            {
                Insert(cmp);
                if (auto* c2d = Downcast(cmp))
                    data->Components.Insert(c2d);
            }   
        }

    }
}