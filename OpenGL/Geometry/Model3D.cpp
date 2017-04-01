#include "Geometry/Model3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/
        Model3D& Model3D::Geometry(const Geometry3D& value)
        {
            _geometry = value;
            return *this;
        }



        /** CONSTRUCTORS **/
        Model3D::Model3D() { }
        Model3D::Model3D(const Geometry3D& geometry) :
            _geometry(geometry)
        {

        }

    }
}