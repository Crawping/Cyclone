/* CHANGELOG
 * Written by Josh Grooms on 20160923
 */

#pragma once
#include "SVGAPI.h"
#include "Collections/Array.h"
#include "Geometry/Geometry3D.h"
#include "Geometry/ControlPoint2D.h"
#include "Interfaces/IGeometric2D.h"




namespace Cyclone
{
    namespace { using namespace OpenGL; }

    namespace SVG
    {

        class Geometry2D : public virtual IGeometric2D
        {

            public:

                /** PROPERTIES **/
                const Volume& Bounds()                      const override { return _bounds; }
                SVGAPI Vector<PathCommands> Commands()      const override;
                uint Count()                                const override { return ControlPoints.Count(); }
                SVGAPI const GeometryData& Data()           const override;
                SVGAPI Vector<uint> Indices()               const override;
                SVGAPI bool IsClosed()                      const override;
                SVGAPI bool IsEmpty()                       const override;
                SVGAPI Vector<Vector3> Mapping()            const override;
                SVGAPI Vector<Vector3> Normals()            const override;
                SVGAPI Vector<Vector3> Points()             const override;
                SVGAPI Vector<float> Parameters()           const override;
                PointTopologies Topology()                  const override { return _topology; }

                SVGAPI Geometry2D& Bounds(const Volume& value);
                SVGAPI Geometry2D& Topology(PointTopologies value);



                /** CONSTRUCTOR **/
                SVGAPI Geometry2D();



                /** STATIC CONSTRUCTORS **/
                SVGAPI static Geometry2D Circle();
                SVGAPI static Geometry2D Line();
                SVGAPI static Geometry2D Rectangle();
                SVGAPI static Geometry2D RoundedRectangle(const Vector2& position = -0.5f, const Vector2& size = 1.0f, float cornerRadius = 0.0f);
                SVGAPI static Geometry2D Star();
                SVGAPI static Geometry2D Triangle();



                /** UTILITIES **/
                SVGAPI void Append(const ControlPoint2D& point);
                SVGAPI void Append(const ICollection<ControlPoint2D>& points);
                //SVGAPI void Insert(uint index, const ControlPoint2D& point);
                SVGAPI void Set(uint index, const ControlPoint2D& point);
                SVGAPI void Remove(uint index);
                SVGAPI void Clear();
                SVGAPI bool Intersects(const LineSegment3D& line) const override;

                Geometry2D* CreateView() const override { return nullptr; }

                ControlPoint2D& operator ()(uint index)         { return ControlPoints(index); }
                const ControlPoint2D& operator ()(uint index)   const { return ControlPoints(index); }

            private:

                Volume                  _bounds;
                PointTopologies        _topology;
                Vector<ControlPoint2D>  ControlPoints;

        };

    }
}
