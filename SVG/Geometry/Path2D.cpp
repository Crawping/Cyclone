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
        Path2D& Path2D::JoinStyle(JoinStyles value)
        {
            _joinStyle = value;
            nvPathParameteri(ID(), PathParameters::JoinStyle, value);
            return *this;
        }
        Path2D& Path2D::Path(const string& value)
        {
            _path = value;
            _pathNeedsUpdate = true;
            return *this;
        }
        Path2D& Path2D::StrokeColor(const Color4& value)    { _strokeColor = value; return *this; }
        Path2D& Path2D::StrokeWidth(float value)            { _strokeWidth = value; return *this; }


        
        /** CONSTRUCTORS & DESTRUCTOR **/
        Path2D::Path2D(uint count) :
            Entity3D(Color4::Transparent, VertexTopologies::Path, Vector<float>()),
            _count(count),
            _id(0),
            _path(""),
            _pathNeedsUpdate(false),
            _strokeColor(Color4::Transparent),
            _strokeWidth(0.0f)
        {
            _id = nvGenPaths(_count);
        }

        Path2D::~Path2D()
        {
            if (_id) { nvDeletePaths(_id, _count); }
        }




        /** UTILITIES **/
        void Path2D::Add(const ControlPoint2D& point)
        {
            Commands.Append(point.Command);
            Coordinates.Append(point.Coordinates);

            _pathNeedsUpdate = true;
        }
        void Path2D::Add(const IArray<ControlPoint2D>& points)
        {
            for (uint a = 0; a < points.Count(); a++)
                Add(points(a));
        }
        void Path2D::Render(const GPU* gpu) const
        {
            Update();
            nvMatrixLoadf(TransformMatrices::ModelView, World().ToArray());
            Stencil(gpu);
            Cover(gpu);
        }



        /** PROTECTED UTILITIES **/
        void Path2D::Cover(const GPU* gpu) const
        {
            int varID = glGetUniformLocation(gpu->RenderPipeline()->ID(), "InputColor");
            if (varID != -1)
                glUniform4f(varID, Color().R, Color().G, Color().B, Color().A);

            nvCoverFillPath(ID(), CoverMode());
        }
        void Path2D::Stencil(const GPU* gpu) const
        {
            nvStencilFillPath(ID(), FillMode(), 0x1F);
        }
        void Path2D::Update() const
        {
            if (!_pathNeedsUpdate) { return; }
            if (_path.size())
                nvPathString(ID(), PathFormats::SVG, _path.size(), _path.c_str());

            if (Commands.Count())
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
    }
}
