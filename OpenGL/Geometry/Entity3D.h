/* CHANGELOG
 * Written by Josh Grooms on 20150929
 */

#pragma once
//#include "EnumerationsGL.h"
//#include "Geometry/Geometry3D.h"
//#include "GL/OpenGLAPI.h"
//#include "Imaging/Color4.h"
#include "Interfaces/IRenderable.h"
#include "Libraries/Material3D.h"
//#include "Spatial/Volume.h"
#include "Models/Model3D.h"



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
                const Geometry3D& Geometry()                            const { return _model.Geometry(); }
                const Vector3& Orientation()                            const override { return _model.Orientation(); }    
                const Vector3& Position()                               const override { return _model.Orientation(); }
                const Vector3& Scale()                                  const override { return _model.Orientation(); }

                Entity3D& Geometry(const Geometry3D& value)
                {
                    _model.Geometry(value);
                    return *this;
                }
                Entity3D& Orientation(const Vector3& value)             override
                {
                    _model.Orientation(value);
                    return *this;
                }
                Entity3D& Position(const Vector3& value)                override
                {
                    _model.Position(value);
                    return *this;
                }
                Entity3D& Scale(const Vector3& value)                   override
                {
                    _model.Scale(value);
                    return *this;
                }



                /** MATERIAL PROPERTIES **/
                /// <summary> Gets a reference to the primary color of the entity. </summary>
                virtual const Color4& PrimaryColor()                    const { return Material().PrimaryColor(); }
                /// <summary> Gets a reference to the secondary color of the entity. </summary>
                virtual const Color4& SecondaryColor()                  const { return Material().SecondaryColor(); }
                /// <summary> Gets a pointer to the texture associated with an entity. </summary>
		        virtual const Texture3D* Texture()                      const { return Material().Texture(); }

                /// <summary> Sets the primary color of the entity. </summary>
                virtual Entity3D& PrimaryColor(const Color4& value)
                { 
                    _material.PrimaryColor(value);
                    return *this;
                }
                /// <summary> Sets the secondary color of the entity. </summary>
                virtual Entity3D& SecondaryColor(const Color4& value)
                {
                    _material.SecondaryColor(value);
                    return *this;
                }
                /// <summary> Sets the texture to be used when rendering the entity. </summary>
                virtual Entity3D& Texture(Texture3D* value)
                {
                    _material.Texture(value);
                    return *this;
                }


                
                /** RENDERABLE INTERFACE PROPERTIES **/
                /// <summary> Gets whether the entity is visible in the rendered environment. </summary>
                virtual bool IsVisible()                                const override { return _isVisible; }
                /// <summary> Gets the material used to style the entity in the rendered environment. </summary>
                virtual const Material3D& Material()                    const override { return _material; }

                virtual const Model3D& Model()                          const override { return _model; }

                /// <summary> Sets whether the entity is visible in a rendered environment. </summary>
                virtual Entity3D& IsVisible(bool value)
                {
                    _isVisible = value;
                    return *this;
                }
                /// <summary> Sets the material used to style the entity in the rendered environment. </summary>
                virtual Entity3D& Material(const Material3D& value)
                { 
                    _material = value;
                    return *this;
                }

                virtual Entity3D& Model(const Model3D& value)
                {
                    _model = value;
                    return *this;
                }



                /** CONSTRUCTOR & DESTRUCTOR **/
                Entity3D(): _isVisible(true) { }
                Entity3D(const Model3D& model):
                    _isVisible(true),
                    _model(model)
                {

                }
                /// <summary> Destroys any special resources held by this entity. </summary>
                /// <remarks> The destructor for this base class actually performs no actions whatsoever. </remarks>
                virtual ~Entity3D() { }



                /** UTILITIES **/
                Entity3D& Rotate(const Vector3& values)
                {
                    _model.Rotate(values);
                    return *this;
                }


            protected:

                //virtual Transform3D& Transform() { return _model.Transform(); }

            private:
                
                /** PROPERTY DATA **/
                bool            _isVisible;
                Material3D      _material;
                Model3D         _model;

        };
    }
}
