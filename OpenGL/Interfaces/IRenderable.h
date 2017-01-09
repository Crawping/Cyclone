/* CHANGELOG
 * Written by Josh Grooms on 20160606
 */

#pragma once
#include "Collections/List.h"
#include "Interfaces/IGeometric.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace OpenGL
    {        
        /** FORWARD DECLARATIONS **/
        class IMaterial;
        class IRenderStage;
        class ITransformable;

        /// <summary> An interface that represents a generalized three-dimensional renderable object. </summary>
        class IRenderable
        {

            public:

                /** PROPERTIES **/
                /// <summary> Gets a list of other entities that comprise or are associated with the renderable entity. </summary>
                virtual List<const IRenderable&> Components()       const = 0;
                /// <summary> Gets the geometric data that define the shape of a renderable entity. </summary>
                virtual const IGeometric& Geometry()                const = 0;
                /// <summary> Gets whether the renderable entity is currently visible in a scene. </summary>
                virtual bool IsVisible()                            const = 0;
                /// <summary> Gets the material associated with the renderable entity. </summary>
                virtual const IMaterial& Material()                 const = 0;
                /// <summary> Gets the transformation matrices used to orient, position, and scale a renderable entity within a scene. </summary>
                virtual const ITransformable& Transforms()          const = 0;



                /** DESTRUCTOR **/
                virtual ~IRenderable() { }

        };

    }
}
