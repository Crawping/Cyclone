/* CHANGELOG
 * Written by Josh Grooms on 20160606
 */

#pragma once



namespace Cyclone
{
    namespace Utilities { struct LineSegment; }
    namespace OpenGL
    {        
        /** FORWARD DECLARATIONS **/
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
                virtual const IMaterial& Material()                 const = 0;
                /// <summary> Gets the data that define the spatial properties of a renderable entity. </summary>
                virtual const IModel& Model()                       const = 0;



                /** DESTRUCTOR **/
                virtual ~IRenderable() { }



                /** UTILITIES **/
                virtual bool Intersects(const LineSegment& line)    const = 0;
        };

    }
}
