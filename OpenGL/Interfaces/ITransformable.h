/* CHANGELOG
 * Written by Josh Grooms on 20161228
 */

#pragma once
#include "Math/Matrix4x4.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace Utilities { struct ITransformation3D; }
    namespace OpenGL
    {

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



        /// <summary> An interface that represents a set of generalized spatial transformations for renderable entities. </summary>
        class ITransformable
        {

            public:

                /** PROPERTIES **/

                virtual const TransformData& Data()         const = 0;
                /// <summary> Gets the transformation data that define the orientation, position, and scaling of the entity in model space. </summary>
                virtual const ITransformation3D& Model()    const = 0;
                /// <summary> Gets the transformation data that define the orientation, position, and scaling of texture mapping coordinates. </summary>
                virtual const ITransformation3D& Texture()  const = 0;
                /// <summary> Gets the transformation data that define the orientation, position, and scaling of the entity in world space. </summary>
                virtual const ITransformation3D& World()    const = 0;



                /** DESTRUCTOR **/
                virtual ~ITransformable() { }

        };
    }
}
