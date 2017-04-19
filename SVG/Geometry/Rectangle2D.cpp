#include "NVPR.h"
#include "Utilities.h"
#include "Geometry/Rectangle2D.h"
#include "Geometry/Geometry2D.h"



namespace Cyclone
{
    namespace SVG
    {

        /** PROPERTIES **/
        Rectangle2D& Rectangle2D::CornerRadius(float value)
        {
            _geometry(0).Coordinates.Last() = value;
            NeedsUpdate = true;
            return *this;
        }
        Rectangle2D& Rectangle2D::Offset(const Vector3& value)
        {
            Path2D::Offset(value);
            NeedsUpdate = true;
            return *this;
        }
        Rectangle2D& Rectangle2D::Size(const Vector3& value)
        {
            Path2D::Size(value);
            float x = -value.X / 2.0f, y = -value.Y / 2.0f;
            _geometry.Set(0, { PathCommands::RoundedRectangle, { x, y, value.X, value.Y, CornerRadius() } });
            _geometry.Bounds(Area(x, y, value.X, value.Y));
            NeedsUpdate = true;
            return *this;
        }



        /** CONSTRUCTOR **/
        Rectangle2D::Rectangle2D() : 
            Path2D(Geometry2D::RoundedRectangle()),
            NeedsUpdate(true)
        {

        }



        /** UTILITIES **/
        void Rectangle2D::Update() const
        {
            if (NeedsUpdate)
                UpdateGeometry();

            NeedsUpdate = false;
            Entity2D::Update();
        }


        void Rectangle2D::UpdateGeometry() const
        {
            auto cmds = _geometry.Commands();
            auto crds = _geometry.Parameters();

            nvPathCommands
            (
                ID(),
                cmds.Count(),
                (const ubyte*)(cmds.ToArray()),
                crds.Count(),
                NumericFormats::Float,
                crds.ToArray()
            );

            nvTransformPath(ID(), ID(), TransformTypes::Translate3D, &(Entity2D::Offset().X));
        }
    }
}