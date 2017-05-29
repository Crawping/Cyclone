/* CHANGELOG
 * Written by Josh Grooms on 20161101
 */

#pragma once
#include "EnumerationsGL.h"
#include "Collections/Vector.h"
#include "Interfaces/IGraphicsResource.h"
#include "Spatial/Volume.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }
    namespace OpenGL
    {
        /** FORWARD DECLARATIONS **/
        struct GeometryData
        {
            Volume              Bounds;
            Vector<uint>        Indices;
            Vector<Vector3>     Mapping;
            Vector<Vector3>     Normals;
            Vector<Vector3>     Points;
            PointTopologies     Topology;
        };



        /// <summary> An interface that represents a generalized three-dimensional geometric shape. </summary>
        class IGeometric : public virtual IGraphicsResource
        {

            public:

                /** PROPERTIES **/
                /// <summary> Gets the bounding volume of the 3D geometric shape. </summary>
                virtual const Volume& Bounds()      const = 0;
                /// <summary> Gets the number of points that are used to define the 3D geometric shape. </summary>
                virtual uint Count()                const = 0;
                /// <summary> Gets a structure containing all of the data used to render the 3D geometric shape. </summary>
                virtual const GeometryData& Data()  const = 0;
                /// <summary> Gets an array of indices that define the order in which <see cref="Points"/> is rendered. </summary>
                /// <remarks>
                ///     Not all geometry will be composed of indexable control points or vertices. In those cases, this method will
                ///     return an empty array.
                /// </remarks>
                virtual Vector<uint> Indices()      const = 0;
                /// <summary> Gets whether the 3D geometric shape is currently defined by any points. </summary>
                virtual bool IsEmpty()              const { return Count() == 0; }
                /// <summary> Gets an array of values that map each geometric point onto some other external resource. </summary>
                /// <remarks>
                ///     Typically, these values will be used to map the points of some shape onto textures, although use of other
                ///     resources such as buffers is possible as well.
                /// </remarks>
                virtual Vector<Vector3> Mapping()   const = 0;
                /// <summary> Gets an array of normal vectors associated with each point of the geometric shape. </summary>
                virtual Vector<Vector3> Normals()   const = 0;
                /// <summary> Gets an array of points that define a 3D geometric shape. </summary>
                /// <remarks>
                ///     This property is meant to be interpretted in one of a few possible ways. Most commonly, the name 'Points' will
                ///     refer to the array of vertices that make up the standard polygons, points, and lines that OpenGL is well-known
                ///     for rendering. However, it may also refer to the control points of either a 3D patch object or 2D path object
                ///     (note the lack of a 'c' in the latter; though similarly named, the two are very different things).
                /// </remarks>
                virtual Vector<Vector3> Points()    const = 0;
                /// <summary> Gets an enumerator that represents the type of primitive geometry defined by the <see cref="Points"/> property. </summary>
                virtual PointTopologies Topology()  const = 0;



                /** DESTRUCTOR **/
                virtual ~IGeometric() { }

        };
    }
}
