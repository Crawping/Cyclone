/* CHANGELOG
 * Written by Josh Grooms on 20160923
 */

#pragma once
#include "Collections/Vector.h"
#include "Geometry/Geometry3D.h"
#include "Geometry/ControlPoint2D.h"
#include "SVGAPI.h"




namespace Cyclone
{
    namespace { using namespace OpenGL; }

    namespace SVG
    {

        class GeometrySVG : public Geometry3D
        {

            public:

                /** SVG PROPERTIES **/
                SVGAPI Vector<PathCommands> Commands()      const; //{ return Vector<PathCommands>(); }
                SVGAPI bool IsClosed()                      const; //{ return true; }
                SVGAPI bool IsEmpty()                       const;
                SVGAPI Vector<float> Parameters()           const; // { return Vector<float>(); }



                /** 3D GEOMETRY PROPERTIES **/
                Vector<uint> Indices()              const override { return Vector<uint>(); }
                Vector<Vector3> Mapping()           const override { return Vector<Vector3>(); }
                Vector<Vector3> Normals()           const override { return Vector<Vector3>(); }
                Vector<Vector3> Points()            const override { return Vector<Vector3>(); }
                //VertexTopologies Topology()         const override { return VertexTopologies::Path; }




            private:

                Vector<ControlPoint2D> ControlPoints;

        };


        namespace Geometry2D
        {

            //SVGAPI Vector<ControlPoint2D> Circle();

            SVGAPI Vector<ControlPoint2D> Line();

            SVGAPI Vector<ControlPoint2D> Point();

            SVGAPI Vector<ControlPoint2D> Rectangle();

            SVGAPI Vector<ControlPoint2D> RoundedRectangle();
            
            SVGAPI Vector<ControlPoint2D> Star();

            SVGAPI Vector<ControlPoint2D> Triangle();

        }
    }
}
