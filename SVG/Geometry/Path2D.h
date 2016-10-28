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
#include "Interfaces/IRenderable2D.h"
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
                /// <summary> Gets the color of the path's fill area. </summary>
                virtual const Color4& FillColor()       const { return PrimaryColor(); }

                virtual FillModes FillMode()            const { return _fillMode; }
                /// <summary> Gets the unique numeric identifier for the path object on the GPU. </summary>
                virtual uint ID()                       const { return _id; }
                /// <summary> Gets the end cap style used to initiate path segments. </summary>
                virtual EndCaps InitialCap()            const { return _initialCap; }
                /// <summary> Gets whether the path object has been terminated by a close command. </summary>
                virtual bool IsClosed()                 const { return !Commands.IsEmpty() && (Commands(Commands.Count() - 1) == PathCommands::Close); }
                /// <summary> Gets whether the path has any stored commands. </summary>
                virtual bool IsEmpty()                  const { return Commands.Count() == 0; }
                /// <summary> Gets the joint style used to connect two path segments. </summary>
                virtual JoinStyles JoinStyle()          const { return _joinStyle; }
                /// <summary> Gets the color of the path's surrounding stroke. </summary>
                virtual const Color4& StrokeColor()     const { return SecondaryColor(); }
                /// <summary> Gets the width of the path's surrounding stroke. </summary>
                virtual float StrokeWidth()             const { return _strokeWidth; }
                /// <summary> Gets the end cap style used to terminate path segments. </summary>
                virtual EndCaps TerminalCap()           const { return _terminalCap; }


                SVGAPI virtual Path2D& CoverMode(CoverModes value);

                SVGAPI virtual Path2D& FillMode(FillModes value);
                /// <summary> Sets the end cap style used to initiate path segments. </summary>
                SVGAPI virtual Path2D& InitialCap(EndCaps value);
                /// <summary> Sets the joint style used to connect two path segments. </summary>
                SVGAPI virtual Path2D& JoinStyle(JoinStyles value);

                SVGAPI virtual Path2D& Path(const string& value);
                /// <summary> Sets the color of the path's surrounding stroke. </summary>
                SVGAPI virtual Path2D& StrokeColor(const Color4& value);
                /// <summary> Sets the width of the path's surrounding stroke. </summary>
                SVGAPI virtual Path2D& StrokeWidth(float value);
                /// <summary> Sets the end cap style used to terminate path segments.  </summary>
                SVGAPI virtual Path2D& TerminalCap(EndCaps value);



                /** CONSTRUCTOR & DESTRUCTOR **/
                SVGAPI Path2D(uint count = 1);
                SVGAPI ~Path2D();



                /** UTILITIES **/
                SVGAPI virtual Path2D& Add(const ControlPoint2D& point);
                SVGAPI virtual Path2D& Add(const ICollection<ControlPoint2D>& points);
                SVGAPI virtual void Clear();

                SVGAPI virtual void Fill()              const override;
                SVGAPI virtual void Stroke()            const override;
                SVGAPI virtual void Update()            const override;

            protected:

                /** DATA **/
                List<PathCommands>  Commands;
                List<float>         Coordinates;



                /** PROPERTIES **/
                void ParamsNeedUpdate(bool value)       const { _paramsNeedUpdate = _paramsNeedUpdate ? true : value; }
                void PathNeedsUpdate(bool value)        const { _pathNeedsUpdate = _pathNeedsUpdate ? true : value; }

                SVGAPI virtual void UpdatePath()        const;
                SVGAPI virtual void UpdateParameters()  const;

            private:

                /** PROPERTY DATA **/
                uint                _count;
                CoverModes          _coverMode;
                FillModes           _fillMode;
                uint                _id;
                EndCaps             _initialCap;
                JoinStyles          _joinStyle;
                string              _path;
                mutable bool        _paramsNeedUpdate;
                mutable bool        _pathNeedsUpdate;
                float               _strokeWidth;
                EndCaps             _terminalCap;

        };
    }
}
