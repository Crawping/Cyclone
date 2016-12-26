#include "Scenes/SceneComponent.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/
        SceneComponent& SceneComponent::CullingMode(CullingModes value)         { _settings.CullingMode = value; return *this; }
        SceneComponent& SceneComponent::IsBlendEnabled(bool value)              { _settings.IsBlendEnabled = value; return *this; }
        SceneComponent& SceneComponent::IsDepthTestEnabled(bool value)          { _settings.IsDepthTestEnabled = value; return *this; }
        SceneComponent& SceneComponent::IsStencilTestEnabled(bool value)        { _settings.IsStencilTestEnabled = value; return *this; }
        SceneComponent& SceneComponent::IsVisible(bool value)                   { _isVisible = value; return *this; }
        SceneComponent& SceneComponent::Pipeline(GraphicsPipeline* value)       { _settings.Pipeline = value; return *this; }
        SceneComponent& SceneComponent::Projection(ITransformation3D* value)    { _settings.Projection = value; return *this; }
        SceneComponent& SceneComponent::Target(FrameBuffer* value)              { _settings.Target = value; return *this; }
        SceneComponent& SceneComponent::View(ITransformation3D* value)          { _settings.View = value; return *this; }

        SceneComponent& SceneComponent::Settings(const GraphicsSettings& value)
        {
            return CullingMode(value.CullingMode)
                .IsBlendEnabled(value.IsBlendEnabled)
                .IsDepthTestEnabled(value.IsDepthTestEnabled)
                .IsStencilTestEnabled(value.IsStencilTestEnabled)
                .Pipeline(value.Pipeline)
                .Projection(value.Projection)
                .Target(value.Target)
                .View(value.View);
        }



        /** CONSTRUCTOR **/
        SceneComponent::SceneComponent(const string& name, ISceneLayer& parent) : 
            _isVisible(true),
            _name(name),
            _needsUpdate(false),
            _parent(parent)
        {

        }



        /** UTILITIES **/
        bool SceneComponent::Contains(const IRenderable& entity) const
        {
            return Entities.Contains(&entity);
        }
        void SceneComponent::Insert(const IRenderable& entity)
        {
            Entities.Insert(&entity);
            NeedsUpdate(true);
        }
        void SceneComponent::Update()
        {
            _needsUpdate = false;
        }

    }
}