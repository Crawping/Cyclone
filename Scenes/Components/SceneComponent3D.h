/* CHANGELOG
 * Written by Josh Grooms on 20170415
 */

#pragma once
#include "Components/SceneComponent.h"
#include "Geometry/Entity3D.h"
//#include "Collections/Set.h", 
//#include "Collections/String.h"
//#include "Interfaces/ISceneComponent.h"
//#include "Spatial/Volume.h"
//#include "Spatial/Transform.h"
//#include "SceneAPI.h"



namespace Cyclone
{
    namespace Scenes
    {
        class SceneComponent3D:
            public SceneComponent
        {

            public:

                /** PROPERTIES **/
                Resource<IRenderable> Model()               const override { return _model; }
                const Vector3& Orientation()                const override { return _transform.Orientation(); }
                const Vector3& Position()                   const override { return _transform.Position(); }
                const Vector3& Scale()                      const override { return _transform.Scale(); }
                const Transform3D& Transform()              const override { return _transform; }
                
                SceneAPI SceneComponent3D& Model(Resource<Entity3D> value);
                SceneAPI SceneComponent3D& Orientation(const Vector3& value)    override;
                SceneAPI SceneComponent3D& Position(const Vector3& value)       override;
                SceneAPI SceneComponent3D& Scale(const Vector3& value)          override;
                SceneAPI SceneComponent3D& Transform(const Transform3D& value);



                /** CONSTRUCTOR **/
                SceneAPI SceneComponent3D(ISceneComponent& parent);



                /** UTILITIES **/
                //SceneAPI bool Contains(const Vector3& point)                const override;
                //SceneAPI bool Contains(const ISceneComponent& child)        const override;
                //SceneAPI void Insert(ISceneComponent* child);
                //SceneAPI bool Intersects(const Vector<Vector3, 2>& line)    const;
                //SceneAPI void Remove(const ISceneComponent* child);
                //SceneAPI void Update() override;

            protected:
                
                SceneAPI void UpdateBounds();

            private:

                //Entity3D*       _model;
                Resource<Entity3D>      _model;
                //Resource<Material3D>    _material;
                //Resource<Model3D>       _model;
                Transform3D             _transform;

        };
    }
}
