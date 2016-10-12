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
        Path2D& Path2D::StrokeColor(const Color4& value)    { _strokeColor = value; return *this; }
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
            _strokeColor(Color4::Black),
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
        void Path2D::Render() const
        {
            if (!IsVisible()) { return; }

            Update();
            nvMatrixLoadf(TransformMatrices::ModelView, World().ToArray());
            
            if (Color() != Color4::Transparent)
            {                
                StencilFill();
                CoverFill();
            }

            if (StrokeWidth() != 0.0f)
            {
                StencilStroke();
                CoverStroke();
            }
        }



        /** PROTECTED UTILITIES **/
        void Path2D::CoverFill() const
        {
            //gpu->SetUniform("InputColor", Color());
            nvCoverFillPath(ID(), CoverMode());
        }
        void Path2D::CoverStroke() const
        {
            //gpu->SetUniform("InputColor", StrokeColor());
            nvCoverStrokePath(ID(), CoverMode());
        }
        void Path2D::StencilFill() const
        {
            nvStencilFillPath(ID(), FillMode(), 0x1F);
        }
        void Path2D::StencilStroke() const
        {
            nvStencilStrokePath(ID(), 0x1, ~0);
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
            
            _pathNeedsUpdate = false;
        }

    }
}
