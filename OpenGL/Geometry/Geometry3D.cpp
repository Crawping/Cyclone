//#include "Constants.h"
//#include "Utilities.h"
//#include "Geometry/Geometry3D.h"
//#include "Spatial/Transform.h"
//
//
//
//namespace Cyclone
//{
//    using namespace Utilities;
//
//
//
//    namespace OpenGL
//    {
////
//
//        /** VERTEX UTILITIES **/
//        void Geometry3D::Rotate(Vector<Vertex::Standard>& vertices, const Vector3& rotation)
//        {
//            Transform r = Transform::Rotation(rotation);
//            for (uint a = 0; a < vertices.Count(); a++)
//                vertices(a).Position = Vector3(r * Vector4(vertices(a).Position, 1.0f));
//        }
//        void Geometry3D::Scale(Vector<Vertex::Standard>& vertices, const Vector3& scaling)
//        {
//            for (uint a = 0; a < vertices.Count(); a++)
//                vertices(a).Position *= scaling;
//        }
//        void Geometry3D::Translate(Vector<Vertex::Standard>& vertices, const Vector3& translation)
//        {
//            for (uint a = 0; a < vertices.Count(); a++)
//                vertices(a).Position += translation;
//        }
//
//    }
//}
