#include "Components/SceneComponent.h"
#include "Interfaces/IRenderable.h"



namespace Cyclone
{
    namespace Scenes
    {

        /** PROPERTIES **/
        SceneComponent& SceneComponent::IsVisible(bool value)
        {
            _isVisible = value;
            return *this;
        }
        SceneComponent& SceneComponent::Parent(ISceneComponent& value)
        {
            _parent = value;
            return *this;
        }
        SceneComponent& SceneComponent::Tag(const String& value)
        {
            _tag = value;
            return *this;
        }



        /** CONSTRUCTOR **/
        SceneComponent::SceneComponent(ISceneComponent& parent):
            _isVisible(true),
            _parent(parent)
        {

        }

        

        /** UTILITIES **/
        bool SceneComponent::Contains(const ISceneComponent* child) const
        {
            //return _children.Contains(child);
            return false;
        }
        bool SceneComponent::Intersects(const LineSegment3D& line) const
        {
            return Intersection(line) != nullptr;
        }
        /*bool SceneComponent::Intersects(const Volume& volume) const
        {
            return _bounds.Intersects(volume);
        }*/
        ISceneComponent* SceneComponent::Intersection(const LineSegment3D& line) const
        {
            if (!Bounds().Intersects(line))                         { return nullptr; }
            if (!Model().IsNull() && Model()->Intersects(line))     { return (ISceneComponent*)this; }

            for (uint a = 0; a < _children.Count(); a++)
                if (_children(a)->Intersects(line))     { return _children(a); }

            return nullptr;
        }
        void SceneComponent::Update()
        {

        }



        /** PROTECTED UTILITIES **/
        void SceneComponent::Insert(ISceneComponent* child)
        {
            if (!child) { return; }
            _children.Insert(child);
            UpdateBounds();
        }
        void SceneComponent::Remove(ISceneComponent* child)
        {
            if (!child) { return; }
            _children.Remove(child);
            UpdateBounds();
        }
        void SceneComponent::UpdateBounds()
        {

        }


    }
}