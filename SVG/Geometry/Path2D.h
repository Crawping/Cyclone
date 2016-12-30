/* CHANGELOG
 * Written by Josh Grooms on 20160918
 */

#pragma once
#include "EnumerationsSVG.h"
#include "SVGAPI.h"
#include "Buffers/PathBuffer.h"
#include "Collections/List.h"
#include "Geometry/ControlPoint2D.h"
#include "Geometry/Entity2D.h"
#include "Geometry/Geometry2D.h"
#include "Geometry/PathStyle.h"
#include "Interfaces/IRenderable.h"
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
                /// <summary> Gets the number of individual path instances that have been allocated on the GPU. </summary>
                /// <remarks>
                ///     For almost all imaging-related paths, this property will return a value of <c>1</c>. Values greater
                ///     than <c>1</c> indicate the number of times that a path object is being instanced on the GPU, which
                ///     is almost exclusively used only by text rendering.
                /// </remarks>
                virtual uint InstanceCount()            const { return ControlPoints.InstanceCount(); }

                virtual uint ID()                       const { return ControlPoints.ID(); }



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs a new path object that can be populated with 2D control points. </summary>
                /// <param name="count"> The number of path instances to create. </param>
                SVGAPI Path2D(uint count = 1);

                
                /// <summary> Destroys the path object(s) on the GPU. </summary>
                SVGAPI ~Path2D();



                /** UTILITIES **/
                /// <summary> Appends a new 2D control point to the end of the path command list. </summary>
                /// <param name="point"> A 2D control point containing some path command and its associated input arguments. </param>
                SVGAPI virtual Path2D& Add(const ControlPoint2D& point);
                /// <summary> Appends a collection of 2D control points to the end of the path command list. </summary>
                /// <param name="points"> A collection of 2D control points containing the path commands and associated input arguments. </param>
                SVGAPI virtual Path2D& Add(const ICollection<ControlPoint2D>& points);
                SVGAPI virtual void Clear();

                SVGAPI virtual void Fill()              const override;
                SVGAPI virtual void Stroke()            const override;
                SVGAPI virtual void Update()            const override;

            protected:

                /** DATA **/
                PathBuffer              ControlPoints;



                /** PROPERTIES **/
                bool ParamsNeedUpdate()                 const { return _paramsNeedUpdate; }

                void ParamsNeedUpdate(bool value)       const { _paramsNeedUpdate = _paramsNeedUpdate ? true : value; }



                /** UTILITIES **/
                SVGAPI virtual void UpdateParameters()  const;

            private:

                /** PROPERTY DATA **/
                string              _path;
                mutable bool        _paramsNeedUpdate;

        };
    }
}
