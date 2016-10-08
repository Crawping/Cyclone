/* CHANGELOG 
 * Written by Josh Grooms on 20161007
 */

#pragma once
#include "Collections/List.h"
#include "Geometry/Vertex.h"
#include "Interfaces/IRenderable.h"
#include "Spatial/Volume.h"



namespace Cyclone
{
    namespace OpenGL
    {
        struct SpatialNode
        {
            public:

                SpatialNode() : Nodes(nullptr) { }

            private:
                using IRenderable = const IRenderable3D<Vertex::Standard>*;

                Volume                      Bounds;
                List<IRenderable>           Entities;
                Vector<SpatialNode*, 8>     Nodes;

        };



        class Space3D
        {
            public:
                virtual const Vector3& Position()   const { return 0.0f; }
                virtual const Vector3& Size()       const { return 0.0f; }


            private:
                
                SpatialNode*    Voxel;

                
                


        };
    }
}
