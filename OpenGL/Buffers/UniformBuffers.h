/* CHANGELOG
 * Written by Josh Grooms on 20160523
 */

#pragma once
#include "Color4.h"
#include "TypeDefinitions.h"
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"



/* PERFRAME - A structure containing uniform shader data that are expected to change between every rendered frame. */
struct PerFrame
{
    /* VIEWPROJECTION - The current combined view-projection transformation matrix. */
    Matrix4x4   ViewProjection;
    /* CAMERAPOSITION - The position of the camera in world coordinates. */
    Vector3     CameraPosition;

    uint        Time;
};

/* PEROBJECT - A structure containing uniform shader data that are expected to change between every rendered object. */
struct PerEntity
{
    /* WORLD - The world transformation matrix for an entity. */
    Matrix4x4   World;

    Color4      Color;

    ulong       TextureHandle;

    Vector2     _0;
};





