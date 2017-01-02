#include "GPU.h"
#include "NVPR.h"
#include "Geometry/Path2D.h"
#include "Pipelines/GraphicsPipeline.h"



namespace Cyclone
{
    namespace SVG
    {

        /** PROPERTIES **/
        Path2D& Path2D::Offset(const Vector3& value)
        {
            Entity2D::Offset(value);
            NeedsUpdate = true;
            return *this;
        }
        Path2D& Path2D::Size(const Vector3& value)
        {
            Entity2D::Size(value);
            NeedsUpdate = true;
            return *this;
        }



        /** CONSTRUCTORS & DESTRUCTOR **/
        Path2D::Path2D(uint count) :
            Entity2D(count),
            _paramsNeedUpdate(false),
            NeedsUpdate(true)
        {

        }
        Path2D::Path2D(const Geometry2D& geometry) :
            _geometry(geometry),
            _paramsNeedUpdate(false),
            NeedsUpdate(true)
        {

        }
        Path2D::~Path2D()
        {

        }



        /** UTILITIES **/
        Path2D& Path2D::Add(const ControlPoint2D& point)
        {
            Geometry().Append(point);
            NeedsUpdate = true;
            return *this;
        }
        Path2D& Path2D::Add(const ICollection<ControlPoint2D>& points)
        {
            for (uint a = 0; a < points.Count(); a++)
                Add(points(a));
            NeedsUpdate = true;
            return *this;
        }
        void Path2D::Clear()
        {
            if (IsEmpty()) { return; }
            Geometry().Clear();
            NeedsUpdate = true;
        }
        void Path2D::Update() const
        {
            if (NeedsUpdate)
                UpdateGeometry();

            NeedsUpdate = false;
            Entity2D::Update();
        }



        /** PROTECTED UTILITIES **/
        void Path2D::UpdateGeometry() const
        {
            auto cmds = Geometry().Commands();
            auto crds = Geometry().Parameters();

            nvPathCommands
            (
                ID(),
                cmds.Count(),
                (const ubyte*)(cmds.ToArray()),
                crds.Count(),
                NumericFormats::Float,
                crds.ToArray()
            );

            nvTransformPath(ID(), ID(), TransformTypes::TransposeAffine3D, Transforms().Model().ToArray());
        }

    }
}
