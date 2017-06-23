/* CHANGELOG
 * Written by Josh Grooms on 20160523
 */

#pragma once
#include "TypeDefinitions.h"
#include "Imaging/Color4.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"



namespace Cyclone
{
    namespace Utilities
    {
        struct Color4;
    }
    using namespace Utilities;

    namespace OpenGL
    {
        /// <summary> A structure containing uniform shader data that are expected to change between every rendered frame. </summary>
        struct PerFrame
        {
            /// <summary> The current projection transformation matrix. </summary>
            Matrix4x4   Projection;
            /// </summary> The current view transformation matrix. </summary>
            Matrix4x4   View;
            /// <summary> The position of the camera in world coordinates. </summary>
            Vector3     CameraPosition;
            /// <summary> A time measurement provided by the application for use on the GPU. </summary>
            uint        Time;

            bool operator ==(const PerFrame& other) const
            {
                return 
                    (Projection == other.Projection)            &&
                    (View == other.View)                        &&
                    (CameraPosition == other.CameraPosition)    &&
                    (Time == other.Time);
            }
        };


        /// <summary> A structure containing uniform shader data that are expected to change between every rendered object. </summary>
        struct EntityData
        {
            /// <summary> The linear index of the entity's material data in the associated uniform buffer. </summary>
            uint        MaterialIndex;
            /// <summary> The linear index of the entity's transformation data in the associated uniform buffer. </summary>
            uint        TransformIndex;
            Vector2     _0;

            constexpr EntityData():
                MaterialIndex(0),
                TransformIndex(0)
            {

            }
            constexpr EntityData(uint material, uint transform):
                MaterialIndex(material),
                TransformIndex(transform)
            {

            }

            constexpr bool operator ==(const EntityData& other) const
            {
                return (MaterialIndex == other.MaterialIndex) && (TransformIndex == other.TransformIndex);
            }
        };

        /// <summary> A structure containing uniform shader data that defines the appearance of every rendered object. </summary>
        struct MaterialData
        {
            /// <summary> The primary color of a material. </summary>
            Color4      PrimaryColor;
            /// <summary> The secondary color of a material. </summary>
            Color4      SecondaryColor;
            /// <summary> The numeric handle of a material's texture resource on the GPU. </summary>
            ulong       Texture;
            /// <summary> The minimum value of the material's ambient light term during shading. </summary>
            /// <remarks> 
            ///     This parameter is used during shading to determine the uniform lighting across a material and should 
            ///     take on a value between [0.0f, 1.0f].
            /// </remarks>
            float       Ambience;
            /// <summary> The exponent of the material's specular reflection term during shading. </summary>
            /// <remarks> 
            ///     This parameter is used during shading to determine the size of specular light reflections on a material.
            /// </remarks>
            float       SpecularPower;
            /// <summary> A Boolean indicating whether the material is associated with a texture. </summary>
            uint        IsTextured;

            Vector3     _0;

            /// <summary> Constructs a default material data structure that can be used on the GPU. </summary>
            constexpr MaterialData():
                Texture(0),
                Ambience(0.1f),
                SpecularPower(200),
                IsTextured(false)
            {

            }
            constexpr MaterialData(Color4 primary, Color4 secondary, ulong texture, float ambience, float specularity, bool isTextured):
                PrimaryColor(primary),
                SecondaryColor(secondary),
                Texture(texture),
                Ambience(ambience),
                SpecularPower(specularity),
                IsTextured(isTextured)
            {

            }

            /// <summary> Determines whether two material data structures are equivalent. </summary>
            constexpr bool operator ==(const MaterialData& other) const
            {
                return
                    (Texture == other.Texture)                  &&
                    (PrimaryColor == other.PrimaryColor)        &&
                    (SecondaryColor == other.SecondaryColor);
            }
        };

        /// <summary> A structure containing uniform shader data that defines the model, texture, and world transformations for every rendered object. </summary>
        struct TransformData
        {
            /** DATA **/
            /// <summary> The transformation matrix that orients, positions, and scales the entity in model space. </summary>
            Matrix4x4 Model;
            /// <summary> The transformation matrix that orients, positions, and scales the texture coordinates associated with an entity. </summary>
            Matrix4x4 Texture;
            /// <summary> The transformation matrix that orients, positions, and scales the entity in world space. </summary>
            Matrix4x4 World;

            /** OPERATORS **/
            bool operator ==(const TransformData& other) const
            {
                return
                    (Model == other.Model)      &&
                    (Texture == other.Texture)  &&
                    (World == other.World);
            }
        };

    }
}
