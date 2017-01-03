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
            NeedsUpdate(true)
        {

        }
        Path2D::Path2D(const Geometry2D& geometry) :
            _geometry(geometry),
            NeedsUpdate(true)
        {

        }
        Path2D::~Path2D()
        {

        }



        /** UTILITIES **/
        Path2D& Path2D::Append(const ControlPoint2D& point)
        {
            _geometry.Append(point);
            NeedsUpdate = true;
            return *this;
        }
        Path2D& Path2D::Append(const ICollection<ControlPoint2D>& points)
        {
            _geometry.Append(points);
            NeedsUpdate = true;
            return *this;
        }
        void Path2D::Clear()
        {
            if (IsEmpty()) { return; }
            _geometry.Clear();
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

            Matrix4x4 model = Transforms().Model().ToMatrix4x4();
            nvTransformPath(ID(), ID(), TransformTypes::TransposeAffine3D, model.Transpose().ToArray());
        }

    }
}
