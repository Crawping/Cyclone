/* CHANGELOG
 * Written by Josh Grooms on 20160829
 */

#pragma once
#include "Math/Array.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** FORWARD DECLARATIONS **/
        struct VertexAttribute;
        using namespace Cyclone::Utilities;



        /// <summary> An interface used to designate any data structure as a rendering vertex. </summary>
        struct IVertex
        {
            /// <summary> Gets the exact definition of the vertex data structure for use with OpenGL. </summary>
            /// <returns> An array of vertex attributes that define the format of the vertex structure. </returns>
            virtual Array<VertexAttribute> Layout() const = 0;
            /// <summary> Destroys any rendering- or heap-allocated resources held by the vertex. </summary>
            virtual ~IVertex() { }
        };
    }
}