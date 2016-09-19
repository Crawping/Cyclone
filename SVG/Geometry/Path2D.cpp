#include "Geometry/Path2D.h"
#include "NVPR.h"



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
            _count(count),
            _fillColor(Color4::Transparent),
            _id(0),
            _path(""),
            _strokeColor(Color4::Transparent),
            _strokeWidth(0.0f)
        {
            _id = nvGenPaths(_count);
        }

        //Path2D::Path2D(const string& path) :
        //    _fillColor(Color4::Black),
        //    _id(0),
        //    _joinStyle(JoinStyles::None),
        //    _path(path),
        //    _strokeColor(Color4::Black),
        //    _strokeWidth(0.0f)
        //{
        //    _id = nvGenPaths(1);
        //}


        Path2D::~Path2D()
        {
            if (_id) { nvDeletePaths(_id, _count); }
        }

    }
}

