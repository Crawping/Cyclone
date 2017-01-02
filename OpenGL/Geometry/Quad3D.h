/* CHANGELOG
 * Written by Josh Grooms on 20150908
 */

#pragma once
//#include "Geometry/Entity3D.h"
#include "Geometry/Mesh3D.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Quad3D : public Mesh3D
        {

            public:
                /** CONSTRUCTOR **/
                Quad3D(bool isIndexed = false) : 
                    Mesh3D(Geometry3D::Quad(isIndexed)) 
                { 
                
                }

        };
    }
}
