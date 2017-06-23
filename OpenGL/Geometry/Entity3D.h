/* CHANGELOG
 * Written by Josh Grooms on 20150929
 */

#pragma once
#include "Interfaces/IRenderable.h"
#include "Interfaces/IRenderStage.h"
#include "IO/Event.h"
#include "Libraries/Material3D.h"
#include "Models/Model3D.h"
#include "Resources/Resource.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Texture3D;
    
        class Entity3D: 
            public virtual IRenderable,
            public virtual ITransformable3D
        {

            public:

                /** MODEL PROPERTIES **/
                /// <summary> Gets the data that define the spatial properties of the entity. </summary>
                Resource<Geometry3D> Geometry()                         const { return Model()->Geometry(); }
                /// <summary> Gets the orientation of the entity in world space. </summary>
                const Vector3& Orientation()                            const override { return _transform.Orientation(); }    
                const Vector3& Position()                               const override { return _transform.Orientation(); }
                const Vector3& Scale()                                  const override { return _transform.Orientation(); }

                OpenGLAPI Entity3D& Geometry(Resource<Geometry3D> value);
                OpenGLAPI Entity3D& Orientation(const Vector3& value)             override;
                OpenGLAPI Entity3D& Position(const Vector3& value)                override;
                OpenGLAPI Entity3D& Scale(const Vector3& value)                   override;



                /** MATERIAL PROPERTIES **/
                virtual float Ambience()                                const { return Material()->Ambience(); }
                /// <summary> Gets a reference to the primary color of the entity. </summary>
                virtual const Color4& PrimaryColor()                    const { return Material()->PrimaryColor(); }
                /// <summary> Gets a reference to the secondary color of the entity. </summary>
                virtual const Color4& SecondaryColor()                  const { return Material()->SecondaryColor(); }

                virtual float SpecularPower()                           const { return Material()->SpecularPower(); }
                /// <summary> Gets a pointer to the texture associated with an entity. </summary>
                virtual const ITexture* Texture()                       const { return Material()->Texture(); }

                OpenGLAPI virtual Entity3D& Ambience(float value);
                /// <summary> Sets the primary color of the entity. </summary>
                OpenGLAPI virtual Entity3D& PrimaryColor(const Color4& value);
                /// <summary> Sets the secondary color of the entity. </summary>
                OpenGLAPI virtual Entity3D& SecondaryColor(const Color4& value);

                OpenGLAPI virtual Entity3D& SpecularPower(float value);
                /// <summary> Sets the texture to be used when rendering the entity. </summary>
                OpenGLAPI virtual Entity3D& Texture(Resource<ITexture> value);


                
                /** RENDERABLE INTERFACE PROPERTIES **/
                /// <summary> Gets whether the entity is visible in the rendered environment. </summary>
                bool IsVisible()                                        const override { return _isVisible; }
                /// <summary> Gets the material used to style the entity in the rendered environment. </summary>
                Resource<IMaterial> Material()                          const override { return _material; }

                Resource<IModel> Model()                                const override { return _model; }

                //const IGraphicsSettings* Settings()                     const override { return &*_settings; }
                Resource<IGraphicsSettings> Settings()                  const override { return _settings; }

                Resource<IRenderStage> Stage()                          const override { return _stage; }

                const Transform3D& Transform()                          const override { return _transform; }



                /// <summary> Sets whether the entity is visible in a rendered environment. </summary>
                OpenGLAPI virtual Entity3D& IsVisible(bool value);
                /// <summary> Sets the material used to style the entity in the rendered environment. </summary>
                OpenGLAPI virtual Entity3D& Material(Resource<Material3D> value);

                OpenGLAPI virtual Entity3D& Model(Resource<Model3D> value);

                OpenGLAPI virtual Entity3D& Settings(Resource<IGraphicsSettings> value);

                OpenGLAPI virtual Entity3D& Transform(const Transform3D& value);



                /** CONSTRUCTOR & DESTRUCTOR **/
                Entity3D(): _isVisible(true) { }
                Entity3D(Resource<Model3D> model):
                    _isVisible(true),
                    _model(model)
                {

                }



                /** UTILITIES **/
                bool Intersects(const LineSegment3D& line) const override { return false; }

            private:
                
                /** PROPERTY DATA **/
                bool                            _isVisible;
                Resource<Material3D>            _material;
                Resource<Model3D>               _model;
                Resource<IGraphicsSettings>     _settings;
                Resource<IRenderStage>          _stage;
                Transform3D                     _transform;

        };
    }
}
