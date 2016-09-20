/* CHANGELOG
 * Written by Josh Grooms on 20160918
 */

#pragma once
#include "EnumerationsSVG.h"
#include "SVGAPI.h"
#include "Imaging/Color4.h"
#include "Interfaces/IRenderable.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace SVG
    {
        using namespace OpenGL;

        class Path2D : public IRenderable2D<string>
        {
            public:
                virtual uint Count()                const { return _count; }
                virtual CoverModes CoverMode()      const { return _coverMode; }
                virtual const Color4& FillColor()   const { return _fillColor; }
                virtual FillModes FillMode()        const { return _fillMode; }
                virtual uint ID()                   const { return _id; }
                virtual JoinStyles JoinStyle()      const { return _joinStyle; }
                virtual const string& Path()        const { return _path; }
                virtual const Color4& StrokeColor() const { return _strokeColor; }
                virtual float StrokeWidth()         const { return 0.0f; }

                const Color4& Color()               const override { return _fillColor; }
                const Array<uint>& Indices()        const override { return Array<uint>(); }
                bool IsVisible()                    const override { return true; }
                const Array<string>& Points()       const override { return Array<string>(); }
                const Texture2D* Texture()          const override { return nullptr; }
                VertexTopologies Topology()         const override { return VertexTopologies::Path; }
                const Transform& World()            const override { return _world; }



                SVGAPI virtual Path2D& CoverMode(CoverModes value);
                SVGAPI virtual Path2D& FillColor(const Color4& value);
                SVGAPI virtual Path2D& FillMode(FillModes value);
                SVGAPI virtual Path2D& JoinStyle(JoinStyles value);
                SVGAPI virtual Path2D& Path(const string& value);
                SVGAPI virtual Path2D& StrokeColor(const Color4& value);
                SVGAPI virtual Path2D& StrokeWidth(float value);


                SVGAPI Path2D(uint count = 1);
                SVGAPI ~Path2D();


                SVGAPI void Render() const override;

            private:

                uint        _count;
                CoverModes  _coverMode;
                Color4      _fillColor;
                FillModes   _fillMode;
                uint        _id;
                JoinStyles  _joinStyle;
                string      _path;
                Color4      _strokeColor;
                float       _strokeWidth;
                Transform   _world;




        };
    }
}
