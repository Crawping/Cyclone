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
            PathNeedsUpdate(true);
            return *this;
        }
        Path2D& Path2D::StrokeColor(const Color4& value)
        { 
            Entity3D::SecondaryColor(value);
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
            Entity3D(Color4::Transparent, VertexTopologies::Path, Vector<float>()),
            _count(count),
            _id(0),
            _pathNeedsUpdate(false),
            _paramsNeedUpdate(false)
        {
            _id = nvGenPaths(_count);
        }

        Path2D::~Path2D()
        {
            if (_id) { nvDeletePaths(_id, _count); }
        }



        /** UTILITIES **/
        Path2D& Path2D::Add(const ControlPoint2D& point)
        {
            Commands.Append(point.Command);
            Coordinates.Append(point.Coordinates);
            PathNeedsUpdate(true);
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
            Commands.Clear();
            Coordinates.Clear();
            PathNeedsUpdate(true);
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
            UpdatePath();
            UpdateParameters();
        }



        void Path2D::UpdatePath() const
        {
            if (!_pathNeedsUpdate) { return; }

            if (_path.size())
                nvPathString(ID(), PathFormats::SVG, _path.size(), _path.c_str());
            else
                nvPathCommands
                (
                    ID(),
                    Commands.Count(),
                    (const ubyte*)(Commands.ToVector().ToArray()),
                    Coordinates.Count(),
                    NumericFormats::Float,
                    Coordinates.ToVector().ToArray()
                );

            _pathNeedsUpdate = false;
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
