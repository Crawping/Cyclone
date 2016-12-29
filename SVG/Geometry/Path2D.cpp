#include "GPU.h"
#include "NVPR.h"
#include "Geometry/Path2D.h"
#include "Pipelines/GraphicsPipeline.h"



namespace Cyclone
{
    namespace SVG
    {

        /** PROPERTIES **/
        Path2D& Path2D::CoverMode(CoverModes value)
        {
            _style.CoverMode = value;
            return *this;
        }
        Path2D& Path2D::FillMode(FillModes value)
        {
            _style.FillMode = value;
            return *this;
        }
        Path2D& Path2D::InitialCap(EndCaps value)
        {
            _style.InitialCap = value;
            ParamsNeedUpdate(true);
            return *this;
        }
        Path2D& Path2D::JoinStyle(JoinStyles value)
        {
            _style.JoinStyle = value;
            ParamsNeedUpdate(true);
            return *this;
        }
        Path2D& Path2D::Path(const string& value)
        {
            _path = value;
            return *this;
        }
        Path2D& Path2D::StrokeColor(const Color4& value)
        {
            Material().SecondaryColor(value);
            return *this;
        }
        Path2D& Path2D::StrokeWidth(float value)
        {
            _style.StrokeWidth = value;
            ParamsNeedUpdate(true);
            return *this;
        }
        Path2D& Path2D::TerminalCap(EndCaps value)
        {
            _style.TerminalCap = value;
            ParamsNeedUpdate(true);
            return *this;
        }



        /** CONSTRUCTORS & DESTRUCTOR **/
        Path2D::Path2D(uint count) :
            ControlPoints(count),
            _paramsNeedUpdate(false)
        {

        }

        Path2D::~Path2D()
        {

        }



        /** UTILITIES **/
        Path2D& Path2D::Add(const ControlPoint2D& point)
        {
            ControlPoints.Add(point);
            return *this;
        }
        Path2D& Path2D::Add(const ICollection<ControlPoint2D>& points)
        {
            if (points.IsEmpty()) { return *this; }

            for (uint a = 0; a < points.Count(); a++)
                Add(points(a));

            return *this;
        }
        void Path2D::Clear()
        {
            if (IsEmpty()) { return; }
            ControlPoints.Clear();
        }



        /** RENDERING UTILITIES **/
        void Path2D::Fill() const
        {
            if (!IsVisible()) { return; }
            nvStencilFillPath(ID(), FillMode(), 0x1F);
            nvCoverFillPath(ID(), CoverMode());
        }
        void Path2D::Stroke() const
        {
            if (!IsVisible()) { return; }
            nvStencilStrokePath(ID(), 0x1, ~0);
            nvCoverStrokePath(ID(), CoverMode());
        }
        void Path2D::Update() const
        {
            ControlPoints.Update();
            UpdateParameters();
        }



        void Path2D::UpdateParameters() const
        {
            if (!_paramsNeedUpdate) { return; }

            nvPathParameteri(ID(), PathParameters::JoinStyle, JoinStyle());
            nvPathParameteri(ID(), PathParameters::InitialEndCap, InitialCap());
            nvPathParameterf(ID(), PathParameters::StrokeWidth, StrokeWidth());
            nvPathParameteri(ID(), PathParameters::TerminalEndCap, TerminalCap());

            _paramsNeedUpdate = false;
        }
    }
}
