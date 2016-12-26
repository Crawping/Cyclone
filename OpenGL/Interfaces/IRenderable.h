/* CHANGELOG
 * Written by Josh Grooms on 20160606
 */

#pragma once
#include "Collections/List.h"
#include "Interfaces/IGeometric.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace Utilities { struct ITransformation3D; }

    namespace OpenGL
    {        
        class IMaterial;
        class IRenderStage;

        class IRenderable
        {
            public:
                /// <summary> Gets the geometric data that define the shape of a renderable entity. </summary>
                virtual const IGeometric& Geometry()                const = 0;
                /// <summary> Gets whether the renderable entity is currently visible in a scene. </summary>
                virtual bool IsVisible()                            const = 0;
                /// <summary> Gets the material associated with the renderable entity. </summary>
                virtual const IMaterial& Material()                 const = 0;
                /// <summary> Gets the transformation data that define the orientation, position, and scaling of the entity in model space. </summary>
                virtual const ITransformation3D& ModelTransform()   const = 0;

                virtual const ITransformation3D& TextureTransform() const = 0;
                /// <summary> Gets the transformation data that define the orientation, position, and scaling of the entity in world space. </summary>
                virtual const ITransformation3D& WorldTransform()   const = 0;

                virtual ~IRenderable() { }
        };

    }
}
