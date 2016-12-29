/* CHANGELOG
 * Written by Josh Grooms on 20161228
 */

#pragma once



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace Utilities { struct ITransformation3D; }

    namespace OpenGL
    {
        class ITransformable
        {
            public:

                /// <summary> Gets the transformation data that define the orientation, position, and scaling of the entity in model space. </summary>
                virtual const ITransformation3D& Model()    const = 0;

                virtual const ITransformation3D& Texture()  const = 0;
                /// <summary> Gets the transformation data that define the orientation, position, and scaling of the entity in world space. </summary>
                virtual const ITransformation3D& World()    const = 0;

                virtual ~ITransformable() { }

        };
    }
}
