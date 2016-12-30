/* CHANGELOG
 * Written by Josh Grooms on 20151215
 */

#pragma once
#include "SVGAPI.h"
#include "Geometry/Entity3D.h"
#include "Geometry/Geometry2D.h"
#include "Geometry/PathStyle.h"
#include "Interfaces/IRenderable2D.h"



namespace Cyclone
{
    namespace 
    { 
        using namespace OpenGL;
        using namespace Utilities; 
    }

    namespace SVG
    {        

        class Entity2D : 
            public Entity3D,
            public virtual IRenderable2D
        {

            public:
        
                /** STYLE PROPERTIES **/
                virtual CoverModes CoverMode()          const { return _style.CoverMode; }

                virtual FillModes FillMode()            const { return _style.FillMode; }
                /// <summary> Gets the unique numeric identifier for the path object on the GPU. </summary>
                //virtual uint ID()                       const { return ControlPoints.ID(); }
                /// <summary> Gets the end cap style used to initiate path segments. </summary>
                virtual EndCaps InitialCap()            const { return _style.InitialCap; }
                /// <summary> Gets whether the path object has been terminated by a close command. </summary>
                virtual bool IsClosed()                 const { return Geometry().IsClosed(); }
                /// <summary> Gets whether the path has any stored commands. </summary>
                virtual bool IsEmpty()                  const { return Geometry().IsEmpty(); }
                /// <summary> Gets the joint style used to connect two path segments. </summary>
                virtual JoinStyles JoinStyle()          const { return _style.JoinStyle; }
                /// <summary> Gets the width of the path's surrounding stroke. </summary>
                virtual float StrokeWidth()             const { return _style.StrokeWidth; }

                virtual const PathStyle& Style()        const { return _style; }
                /// <summary> Gets the end cap style used to terminate path segments. </summary>
                virtual EndCaps TerminalCap()           const { return _style.TerminalCap; }


                SVGAPI virtual Entity2D& CoverMode(CoverModes value);

                SVGAPI virtual Entity2D& FillMode(FillModes value);
                /// <summary> Sets the end cap style used to initiate path segments. </summary>
                SVGAPI virtual Entity2D& InitialCap(EndCaps value);
                /// <summary> Sets the joint style used to connect two path segments. </summary>
                SVGAPI virtual Entity2D& JoinStyle(JoinStyles value);
                /// <summary> Sets the width of the path's surrounding stroke. </summary>
                SVGAPI virtual Entity2D& StrokeWidth(float value);

                SVGAPI virtual Entity2D& Style(const PathStyle& value);
                /// <summary> Sets the end cap style used to terminate path segments.  </summary>
                SVGAPI virtual Entity2D& TerminalCap(EndCaps value);



                virtual const GeometrySVG& Geometry()   const override { return (GeometrySVG&)Entity3D::Geometry(); }
                
        
            protected:

                /** PROPERTIES **/
                virtual GeometrySVG& Geometry()         override { return (GeometrySVG&)Entity3D::Geometry(); }
                virtual PathStyle& Style()              { return _style; }



                /** CONSTRUCTORS **/
                Entity2D() { }
                Entity2D(const GeometrySVG& geometry) :
                    Entity3D(geometry)
                {

                }
        
            private:

                /** PROPERTY DATA **/
                PathStyle _style;
        
        };
    }
}