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


        class IModel
        {
            public:
                
                virtual const IGeometric& Geometry()            const = 0;
                virtual bool IsEmpty()                          const { return Geometry().IsEmpty(); }
                virtual const ISpatialTransform& Transform()    const = 0;
        };
    }
}
