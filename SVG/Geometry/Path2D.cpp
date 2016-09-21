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
        Path2D& Path2D::FillColor(const Color4& value)      { _fillColor = value; return *this; }
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
            nvPathString(ID(), PathFormats::SVG, value.size(), value.c_str());
            return *this;
        }
        Path2D& Path2D::StrokeColor(const Color4& value)    { _strokeColor = value; return *this; }
        Path2D& Path2D::StrokeWidth(float value)            { _strokeWidth = value; return *this; }


        
        /** CONSTRUCTORS & DESTRUCTOR **/
        Path2D::Path2D(uint count) :
            Entity3D(Color4::Transparent, VertexTopologies::Path, Array<string>()),
            _count(count),
            _fillColor(Color4::Transparent),
            _id(0),
            _path(""),
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
        void Path2D::Render(const GPU* gpu) const
        {
            nvMatrixLoadf(TransformMatrices::ModelView, World().ToArray());
            Stencil(gpu);
            Cover(gpu);
        }


        /** PROTECTED UTILITIES **/
        void Path2D::Cover(const GPU* gpu) const
        {
            int varID = glGetUniformLocation(gpu->RenderPipeline()->ID(), "InputColor");
            if (varID != -1)
                glUniform4f(varID, FillColor().R, FillColor().G, FillColor().B, FillColor().A);

            nvCoverFillPath(ID(), CoverMode());
        }
        void Path2D::Stencil(const GPU* gpu) const
        {
            nvStencilFillPath(ID(), FillMode(), 0x1F);
        }
    }
}
