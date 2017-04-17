/* CHANGELOG
 * Written by Josh Grooms on 20170415
 */

#pragma once
#include "Collections/Set.h"
#include "Interfaces/ISceneComponent.h"
#include "Spatial/Volume.h"
#include "Spatial/Transform.h"
#include "SceneAPI.h"



namespace Cyclone
{
    namespace Scenes
    {
        class SceneComponent3D : public virtual ISceneComponent
        {

            public:

                /** PROPERTIES **/
                const Volume& Bounds()                      const override { return _bounds; }
                List<ISceneComponent*> Children()           const override { return _children; }
                bool IsVisible()                            const override { return _isVisible; }
                const IRenderable* Model()                  const override { return _model; }
                const ISceneComponent& Parent()             const override { return _parent; }
                const string& Tag()                         const override { return _tag; }
                const Transform& Transformation()           const override { return _transformation; }
                
                SceneAPI SceneComponent3D& IsVisible(bool value) override;
                SceneAPI SceneComponent3D& Model(IRenderable* value);
                SceneAPI SceneComponent3D& Parent(ISceneComponent& value);
                SceneAPI SceneComponent3D& Transformation(const Transform& value);



                /** CONSTRUCTOR **/
                SceneAPI SceneComponent3D(ISceneComponent& parent);



                /** UTILITIES **/
                SceneAPI bool Contains(const Vector3& point)                const override;
                SceneAPI bool Contains(const ISceneComponent& child)        const override;
                SceneAPI void Insert(ISceneComponent& child);
                SceneAPI bool Intersects(const Vector<Vector3, 2>& line)    const;
                SceneAPI void Remove(const ISceneComponent& child);
                SceneAPI void Update() override;

            protected:

                


            private:
                Volume                  _bounds;
                Set<ISceneComponent*>   _children;
                bool                    _isVisible;
                IRenderable*            _model;
                ISceneComponent&        _parent;
                string                  _tag;
                Transform               _transformation;

        };
    }
}
