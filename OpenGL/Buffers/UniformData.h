/* CHANGELOG
 * Written by Josh Grooms on 20160523
 */

#pragma once
#include "Imaging/Color4.h"
#include "TypeDefinitions.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"



namespace Cyclone
{
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
        };

        /// <summary> A structure containing uniform shader data that are expected to change between every rendered object. </summary>
        struct PerEntity
        {
            /// <summary> The world transformation matrix for an entity. </summary>
            Matrix4x4   World;
            /// <summary> The base color of an entity. </summary>
            Color4      Color;
        };

    }
}
