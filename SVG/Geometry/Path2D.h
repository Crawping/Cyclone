/* CHANGELOG
 * Written by Josh Grooms on 20160918
 */

#pragma once
#include "EnumerationsSVG.h"
#include "SVGAPI.h"
#include "Collections/List.h"
#include "Geometry/ControlPoint2D.h"
#include "Geometry/Entity3D.h"
#include "Imaging/Color4.h"
#include "Interfaces/IRenderable.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace SVG
    {
        using namespace OpenGL;

        class Path2D : 
            public Entity3D<float>, 
            public virtual IRenderable2D<float>
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the number of individual path instances that have been allocated on the GPU. </summary>
                /// <remarks>
                ///     For almost all imaging-related paths, this property will return a value of <c>1</c>. Values greater 
                ///     than <c>1</c> indicate the number of times that a path object is being instanced on the GPU, which 
                ///     is almost exclusively used only by text rendering.
                /// </remarks>
                virtual uint InstanceCount()            const { return _count; }
                virtual CoverModes CoverMode()          const { return _coverMode; }
                virtual FillModes FillMode()            const { return _fillMode; }
                /// <summary> Gets the unique numeric identifier for the path object on the GPU. </summary>
                virtual uint ID()                       const { return _id; }
                virtual EndCaps InitialCap()            const { return _initialCap; }
                virtual bool IsClosed()                 const { return !Commands.IsEmpty() && (Commands(Commands.Count() - 1) == PathCommands::Close); }
                /// <summary> Gets whether the path has any stored commands. </summary>
                virtual bool IsEmpty()                  const { return Commands.Count() == 0; }
                virtual JoinStyles JoinStyle()          const { return _joinStyle; }
                /// <summary> Gets the color of the path's surrounding stroke. </summary>
                virtual const Color4& StrokeColor()     const { return _strokeColor; }
                /// <summary> Gets the width of the path's surrounding stroke. </summary>
                virtual float StrokeWidth()             const { return _strokeWidth; }
                virtual EndCaps TerminalCap()           const { return _terminalCap; }

                SVGAPI virtual Path2D& CoverMode(CoverModes value);
                SVGAPI virtual Path2D& FillMode(FillModes value);
                SVGAPI virtual Path2D& InitialCap(EndCaps value);
                SVGAPI virtual Path2D& JoinStyle(JoinStyles value);
                SVGAPI virtual Path2D& Path(const string& value);
                /// <summary> Sets the color of the path's surrounding stroke. </summary>
                SVGAPI virtual Path2D& StrokeColor(const Color4& value);
                /// <summary> Sets the width of the path's surrounding stroke. </summary>
                SVGAPI virtual Path2D& StrokeWidth(float value);
                SVGAPI virtual Path2D& TerminalCap(EndCaps value);



                /** CONSTRUCTOR & DESTRUCTOR **/
                SVGAPI Path2D(uint count = 1);
                SVGAPI ~Path2D();



                /** UTILITIES **/
                SVGAPI virtual Path2D& Add(const ControlPoint2D& point);
                SVGAPI virtual Path2D& Add(const IArray<ControlPoint2D>& points);
                SVGAPI virtual void Clear();
                SVGAPI virtual void Render(const GPU* gpu) const override;

            protected:
                
                /** DATA **/
                List<PathCommands>  Commands;
                List<float>         Coordinates;


                /** RENDERING UTILITIES **/
                SVGAPI virtual void CoverFill(const GPU* gpu)       const;
                SVGAPI virtual void CoverStroke(const GPU* gpu)     const;
                SVGAPI virtual void StencilFill(const GPU* gpu)     const;
                SVGAPI virtual void StencilStroke(const GPU* gpu)   const;
                SVGAPI virtual void Update()                        const;

            private:
                
                /** PROPERTY DATA **/
                uint                _count;
                CoverModes          _coverMode;
                FillModes           _fillMode;
                uint                _id;
                EndCaps             _initialCap;
                JoinStyles          _joinStyle;
                string              _path;
                mutable bool        _pathNeedsUpdate;
                Color4              _strokeColor;
                float               _strokeWidth;
                EndCaps             _terminalCap;

        };
    }
}
