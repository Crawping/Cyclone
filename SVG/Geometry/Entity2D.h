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
        
                /** PROPERTIES **/

                virtual CoverModes CoverMode()          const { return _style.CoverMode; }

                virtual FillModes FillMode()            const { return _style.FillMode; }
                /// <summary> Gets the unique numeric identifier for the path object on the GPU. </summary>
                virtual uint ID()                       const { return _id; }
                /// <summary> Gets the end cap style used to initiate path segments. </summary>
                virtual EndCaps InitialCap()            const { return _style.InitialCap; }
                /// <summary> Gets the number of individual path instances that have been allocated on the GPU. </summary>
                /// <remarks>
                ///     For almost all imaging-related paths, this property will return a value of <c>1</c>. Values greater
                ///     than <c>1</c> indicate the number of times that a path object is being instanced on the GPU, which
                ///     is almost exclusively used only by text rendering.
                /// </remarks>
                virtual uint InstanceCount()            const { return _instanceCount; }
                /// <summary> Gets the joint style used to connect two path segments. </summary>
                virtual JoinStyles JoinStyle()          const { return _style.JoinStyle; }
                /// <summary> Gets the width of the path's surrounding stroke. </summary>
                virtual float StrokeWidth()             const { return _style.StrokeWidth; }
                /// <summary> Gets a structure containing all of the styling data used to render the entity. </summary>
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
                /// <summary> Summarily sets all of the styling data used to render the entity. </summary>
                SVGAPI virtual Entity2D& Style(const PathStyle& value);
                /// <summary> Sets the end cap style used to terminate path segments.  </summary>
                SVGAPI virtual Entity2D& TerminalCap(EndCaps value);



                /** DESTRUCTOR **/
                SVGAPI virtual ~Entity2D();



                /** UTILITIES **/
                SVGAPI virtual void Fill()              const override;
                SVGAPI virtual void Stroke()            const override;
                SVGAPI virtual void Update()            const override;
        
            protected:

                /** PROPERTIES **/
                virtual PathStyle& Style()              { return _style; }



                /** CONSTRUCTORS **/
                SVGAPI Entity2D(uint count = 1);



                /** UTILITIES **/
                SVGAPI virtual void CoverFill()         const;
                SVGAPI virtual void CoverStroke()       const;
                SVGAPI virtual void StencilFill()       const;
                SVGAPI virtual void StencilStroke()     const;
                SVGAPI virtual void UpdateParameters()  const;
        
            private:

                /** PROPERTY DATA **/
                uint            _id;
                uint            _instanceCount;
                PathStyle       _style;

                mutable bool    NeedsUpdate;
        
        };
    }
}