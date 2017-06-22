/* CHANGELOG
 * Written by Josh Grooms on 20170528
 */

#pragma once



namespace Cyclone
{
    namespace Utilities { class ISpatialTransform; }
    namespace OpenGL
    {
        class IGeometric;
        using namespace Utilities;



        /// <summary> An interface that represents a three-dimensional geometric model. </summary>
        class IModel
        {
            public:
                
                virtual Resource<IGeometric> Geometry()         const = 0;
                /// <summary> Gets whether the model has any geometric data. </summary>
                virtual bool IsEmpty()                          const = 0;
                /// <summary> Gets the transformation that converts between local and model space. </summary>
                virtual const ISpatialTransform& Transform()    const = 0;

        };
    }
}
