/* CHANGELOG
 * Written by Josh Grooms on 20170529
 */

#pragma once
#include "Collections/Set.h"
#include "Collections/String.h"
#include "Interfaces/ISceneComponent.h"
#include "Spatial/Volume.h"
#include "Spatial/Transform.h"
#include "SceneAPI.h"



namespace Cyclone
{
    namespace Scenes
    {
        class SceneComponent:
            public virtual ISceneComponent
        {
            public:

                /** PROPERTIES **/
                const Volume& Bounds()                                              const override { return _bounds; }
                List<ISceneComponent*> Children()                                   const override { return _children; }
                bool IsVisible()                                                    const override { return _isVisible; }
                const ISceneComponent& Parent()                                     const override { return _parent; }
                const String& Tag()                                                 const override { return _tag; }
                
                SceneAPI SceneComponent& IsVisible(bool value)                      override;
                SceneAPI SceneComponent& Parent(ISceneComponent& value)             override;
                SceneAPI SceneComponent& Tag(const String& value)                   override;



                /** UTILITIES **/
                SceneAPI bool Contains(const ISceneComponent* child)                const override;
                SceneAPI bool Intersects(const LineSegment3D& line)                 const override;
                //SceneAPI bool Intersects(const Volume& volume)                      const override;
                SceneAPI ISceneComponent* Intersection(const LineSegment3D& line)   const override;
                SceneAPI void Update()                                              override;

            protected:
                
                /** CONSTRUCTOR **/
                SceneAPI SceneComponent(ISceneComponent& parent);



                /** UTILITIES **/
                SceneAPI void Insert(ISceneComponent* child)                override;
                SceneAPI void Remove(ISceneComponent* child)                override;
                SceneAPI void UpdateBounds();

            private:

                Volume                      _bounds;
                Set<ISceneComponent*>       _children;
                bool                        _isVisible;
                ISceneComponent&            _parent;
                String                      _tag;
        };
    }
}
