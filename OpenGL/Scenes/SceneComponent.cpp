#include "Scenes/SceneComponent.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/
        SceneComponent& SceneComponent::CullingMode(CullingModes value)
        {
            _settings.CullingMode = value;
            _needsUpdate = true;
            return *this;
        }
        SceneComponent& SceneComponent::IsBlendEnabled(bool value)
        {
            _settings.IsBlendEnabled = value;
            _needsUpdate = true;
            return *this; }
        SceneComponent& SceneComponent::IsDepthTestEnabled(bool value)
        {
            _settings.IsDepthTestEnabled = value;
            _needsUpdate = true;
            return *this;
        }
        SceneComponent& SceneComponent::IsStencilTestEnabled(bool value)
        {
            _settings.IsStencilTestEnabled = value;
            _needsUpdate = true;
            return *this;
        }
        SceneComponent& SceneComponent::IsVisible(bool value)
        {
            _isVisible = value;
            _needsUpdate = true;
            return *this;
        }
        SceneComponent& SceneComponent::Pipeline(IGraphicsPipeline* value)
        {
            _settings.Pipeline = value;
            _needsUpdate = true;
            return *this;
        }
        SceneComponent& SceneComponent::Projection(ISpatialTransform* value)
        {
            _settings.Projection = value;
            _needsUpdate = true;
            return *this;
        }
        SceneComponent& SceneComponent::Target(FrameBuffer* value)
        {
            _settings.Target = value;
            _needsUpdate = true;
            return *this;
        }
        SceneComponent& SceneComponent::View(ISpatialTransform* value)
        {
            _settings.View = value;
            _needsUpdate = true;
            return *this;
        }

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
        void SceneComponent::Update()
        {
            _needsUpdate = false;
        }


    }
}
