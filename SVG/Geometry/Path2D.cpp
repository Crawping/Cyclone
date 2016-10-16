#include "GPU.h"
#include "NVPR.h"
#include "Geometry/Path2D.h"
#include "Pipelines/GraphicsPipeline.h"



namespace Cyclone
{
    namespace SVG
    {

        /** PROPERTIES **/
        Path2D& Path2D::CoverMode(CoverModes value)         { _coverMode = value; return *this; }
        Path2D& Path2D::FillMode(FillModes value)           { _fillMode = value; return *this; }
        Path2D& Path2D::InitialCap(EndCaps value)
        {
            _initialCap = value;
            _pathNeedsUpdate = true;
            return *this;
        }
        Path2D& Path2D::JoinStyle(JoinStyles value)
        {
            _joinStyle = value;
            _pathNeedsUpdate = true;
            return *this;
        }
        Path2D& Path2D::Path(const string& value)
        {
            _path = value;
            _pathNeedsUpdate = true;
            return *this;
        }
        Path2D& Path2D::StrokeColor(const Color4& value)    { Entity3D::SecondaryColor(value); return *this; }
        Path2D& Path2D::StrokeWidth(float value)            
        { 
            _strokeWidth = value;
            _pathNeedsUpdate = true;
            return *this; 
        }
        Path2D& Path2D::TerminalCap(EndCaps value)
        {
            _terminalCap = value;
            _pathNeedsUpdate = true;
            return *this;
        }

        

        /** CONSTRUCTORS & DESTRUCTOR **/
        Path2D::Path2D(uint count) :
            Entity3D(Color4::Transparent, VertexTopologies::Path, Vector<float>()),
            _count(count),
            _id(0),
            _pathNeedsUpdate(false),
            _strokeWidth(2.0f)
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
            _pathNeedsUpdate = true;
            return *this;
        }
        Path2D& Path2D::Add(const IArray<ControlPoint2D>& points)
        {
            for (uint a = 0; a < points.Count(); a++)
                Add(points(a));

            return *this;
        }
        void Path2D::Clear()
        {
            Commands.Clear();
            Coordinates.Clear();

            _pathNeedsUpdate = true;
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

            nvPathParameteri(ID(), PathParameters::JoinStyle, JoinStyle());
            nvPathParameteri(ID(), PathParameters::InitialEndCap, InitialCap());
            nvPathParameterf(ID(), PathParameters::StrokeWidth, StrokeWidth());
            nvPathParameteri(ID(), PathParameters::TerminalEndCap, TerminalCap());
            
            const Matrix4x4& world3D = World().ToMatrix4x4();
            Vector<float, 12> world2D =
            {
                world3D(0, 0), world3D(1, 0), world3D(2, 0),
                world3D(0, 1), world3D(1, 1), world3D(2, 1),
                world3D(0, 2), world3D(1, 2), world3D(2, 2),
            };

            //nvTransformPath(ID(), ID(), TransformTypes::Affine3D, &world2D(0));

            _pathNeedsUpdate = false;
        }

    }
}
