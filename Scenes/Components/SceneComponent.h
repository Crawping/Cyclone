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
            public virtual IComponent
        {
            public:

                /** PROPERTIES **/
                const Volume& Bounds()                                  const override { return _bounds; }
                List<IComponent*> Children()                            const override { return _children; }
                bool IsEmpty()                                          const override { return Model().IsNull() && _children.IsEmpty(); }
                bool IsVisible()                                        const override { return _isVisible; }
                //const IComponent& Parent()                             const override { return _parent; }
                const String& Tag()                                     const override { return _tag; }
        
                SceneAPI SceneComponent& IsVisible(bool value)          override;
                //SceneAPI SceneComponent& Parent(IComponent& value)     override;
                SceneAPI SceneComponent& Tag(const String& value)       override;



                /** UTILITIES **/
                SceneAPI bool Contains(const IComponent* child)                 const override;
                SceneAPI bool Intersects(const LineSegment3D& line)             const override;
                //SceneAPI bool Intersects(const Volume& volume)                      const override;
                SceneAPI IComponent* Intersection(const LineSegment3D& line)    const override;
                SceneAPI void Update()                                          override;

            protected:
                
                /** CONSTRUCTOR **/
                SceneAPI SceneComponent();



                /** UTILITIES **/
                SceneAPI void Insert(IComponent* child)                override;
                SceneAPI void Remove(IComponent* child)                override;
                SceneAPI void UpdateBounds();

            private:

                Volume                  _bounds;
                Set<IComponent*>        _children;
                bool                    _isVisible;
                //IComponent&             _parent;
                String                  _tag;
        };
    }
}
