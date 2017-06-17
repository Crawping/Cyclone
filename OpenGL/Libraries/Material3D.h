/* CHANGELOG
 * Written by Josh Grooms on 20161204
 */

#pragma once
#include "GL/OpenGLAPI.h" 
#include "Imaging/Color4.h"
#include "Interfaces/IMaterial.h"
#include "Interfaces/ITransformable3D.h"
#include "Textures/Texture3D.h"
#include "Resources/Resource.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {
        
        class Material3D:
            public virtual IMaterial,
            public ITransformable3D
        {
            public:

                /** SPATIAL PROPERTIES **/
                /// <summary> Gets the orientation of the texture transformation. </summary>
                const Vector3& Orientation()                        const override { return _transform.Orientation(); }
                const Vector3& Position()                           const override { return _transform.Position(); }
                const Vector3& Scale()                              const override { return _transform.Scale(); }
                const Transform3D& Transform()                      const override { return _transform; }

                OpenGLAPI Material3D& Orientation(const Vector3& value);
                OpenGLAPI Material3D& Position(const Vector3& value);
                OpenGLAPI Material3D& Scale(const Vector3& value);
                OpenGLAPI Material3D& Transform(const Transform3D& value);



                /** VISUAL PROPERTIES **/

                float Ambience()                                    const override { return _data.Ambience; }
                /// <summary> Gets a structure containing all of the data needed to render the material. </summary>
                const MaterialData& Data()                          const override { return _data; }
                /// <summary> Gets the primary color of the material. </summary>
                const Color4& PrimaryColor()                        const override { return _data.PrimaryColor; }
                /// <summary> Gets the secondary color of the material. </summary>
                const Color4& SecondaryColor()                      const override { return _data.SecondaryColor; }
                
                float SpecularPower()                               const override { return _data.SpecularPower; }
                /// <summary> Gets a pointer to the texture of a material. </summary>
                Resource<ITexture> Texture()                        const override { return _texture; }

                

                /// <summary> The minimum value of the material's ambient light term during shading. </summary>
                /// <remarks> 
                ///     This parameter is used during shading to determine the uniform lighting across a material and should 
                ///     take on a value between [0.0f, 1.0f].
                /// </remarks>
                OpenGLAPI Material3D& Ambience(float value);
                /// <summary> Summarily sets all of the data needed to render the material. </summary>
                OpenGLAPI Material3D& Data(const MaterialData& value);
                /// <summary> Sets the primary color of the material. </summary>
                OpenGLAPI Material3D& PrimaryColor(const Color4& value);
                /// <summary> Sets the secondary color of the material. </summary>
                OpenGLAPI Material3D& SecondaryColor(const Color4& value);
                /// <summary> The exponent of the material's specular reflection term during shading. </summary>
                /// <remarks> 
                ///     This parameter is used during shading to determine the size of specular light reflections on a material.
                /// </remarks>
                OpenGLAPI Material3D& SpecularPower(float value);
                /// <summary> Sets the texture of a material. </summary>
                OpenGLAPI Material3D& Texture(Resource<ITexture> value);



                /** CONSTRUCTOR **/
                /// <summary> Constructs a new black textureless material that can be used to style renderable objects. </summary>
                OpenGLAPI Material3D();



                /** UTILITIES **/
                OpenGLAPI Material3D* CreateView()                  const override;

            private:
                
                /** PROPERTY DATA **/
                MaterialData        _data;
                Resource<ITexture>  _texture;
                Transform3D         _transform;
        };

    }
}
