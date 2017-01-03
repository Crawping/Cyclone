#include "Geometry/Mesh3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/

        Mesh3D& Mesh3D::Geometry(const Geometry3D& value)
        {
            _geometry = value;
            return *this;
        }



        /** CONSTRUCTORS **/
        Mesh3D::Mesh3D() { }
        Mesh3D::Mesh3D(const Geometry3D& geometry) :
            _geometry(geometry)
        {

        }



        /** UTILITIES **/
        void Mesh3D::Append(const Vertex& vertex)
        {
            _geometry.Append(vertex);
        }
        void Mesh3D::Append(const ICollection<Vertex>& vertices)
        {
            _geometry.Append(vertices);
        }
    }
}