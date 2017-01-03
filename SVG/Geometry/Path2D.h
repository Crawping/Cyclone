/* CHANGELOG
 * Written by Josh Grooms on 20160918
 */

#pragma once
#include "EnumerationsSVG.h"
#include "SVGAPI.h"
#include "Collections/List.h"
#include "Geometry/ControlPoint2D.h"
#include "Geometry/Entity2D.h"
#include "Geometry/Geometry2D.h"
#include "Geometry/PathStyle.h"
#include "Interfaces/IRenderable2D.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace SVG
    {
        using namespace OpenGL;
        

        class Path2D : public Entity2D
        {
            public:

                /** PROPERTIES **/
                using Entity2D::Offset;
                using Entity2D::Size;


                virtual const Volume& Bounds()          const { return _geometry.Bounds(); }
                virtual const Geometry2D& Geometry()    const override { return _geometry; }
                /// <summary> Gets whether the path object has been terminated by a close command. </summary>
                virtual bool IsClosed()                 const { return Geometry().IsClosed(); }
                /// <summary> Gets whether the path has any stored commands. </summary>
                virtual bool IsEmpty()                  const { return Geometry().IsEmpty(); }

                SVGAPI virtual Path2D& Size(const Vector3& value)       override;
                SVGAPI virtual Path2D& Offset(const Vector3& value)     override;



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs a new path object that can be populated with 2D control points. </summary>
                /// <param name="count"> The number of path instances to create. </param>
                SVGAPI Path2D(uint count = 1);

                SVGAPI Path2D(const Geometry2D& geometry);
                /// <summary> Destroys the path object(s) on the GPU. </summary>
                SVGAPI ~Path2D();



                /** UTILITIES **/
                SVGAPI virtual void Clear();
                SVGAPI virtual void Update() const override;

            protected:

                Geometry2D          _geometry;



                /** UTILITIES **/
                /// <summary> Appends a new 2D control point to the end of the path command list. </summary>
                /// <param name="point"> A 2D control point containing some path command and its associated input arguments. </param>
                SVGAPI virtual Path2D& Append(const ControlPoint2D& point);
                /// <summary> Appends a collection of 2D control points to the end of the path command list. </summary>
                /// <param name="points"> A collection of 2D control points containing the path commands and associated input arguments. </param>
                SVGAPI virtual Path2D& Append(const ICollection<ControlPoint2D>& points);
                SVGAPI virtual void UpdateGeometry()    const;

            private:

                /** PROPERTY DATA **/

                mutable bool        NeedsUpdate;

        };
    }
}
