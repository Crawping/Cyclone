/* CHANGELOG
 * Written by Josh Grooms on 20160606
 */

#pragma once
#include "Resources/Resource.h"



namespace Cyclone
{
    namespace Utilities 
    {
        class ISpatialTransform;
        struct LineSegment3D;
    }
    namespace OpenGL
    {        
        /** FORWARD DECLARATIONS **/
        struct IGraphicsSettings;
        class IMaterial;
        class IModel;

        using namespace Utilities;

        /// <summary> An interface that represents a generalized three-dimensional renderable object. </summary>
        class IRenderable
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets whether the renderable entity is currently visible in a scene. </summary>
                virtual bool IsVisible()                            const = 0;
                /// <summary> Gets the material associated with the renderable entity. </summary>
                virtual Resource<IMaterial> Material()              const = 0;
                /// <summary> Gets the data that define the spatial properties of a renderable entity. </summary>
                virtual Resource<IModel> Model()                    const = 0;

                virtual const ISpatialTransform& Transform()        const = 0;

                virtual Resource<IGraphicsSettings> Settings()      const = 0;



                /** DESTRUCTOR **/
                virtual ~IRenderable() { }



                /** UTILITIES **/
                virtual bool Intersects(const LineSegment3D& line)    const = 0;
        };

    }
}
