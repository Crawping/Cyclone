/* CHANGELOG
 * Written by Josh Grooms on 20161103
 */

#pragma once
#include "EnumerationsSVG.h"
#include "SVGAPI.h"
#include "Collections/List.h"
#include "Geometry/ControlPoint2D.h"
#include "Interfaces/IDataBuffer.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }

    namespace SVG
    {
        class PathBuffer : public IDataBuffer
        {
            public:

                /** PROPERTIES **/
                uint Count()        const override { return _commands.Count(); }


                
                /** CONSTRUCTOR & DESTRUCTOR **/
                SVGAPI PathBuffer();
                SVGAPI ~PathBuffer();


                SVGAPI void Add(const ControlPoint2D& point);
                SVGAPI void Add(const ICollection<ControlPoint2D>& points);
                SVGAPI void Update();


            private:

                uint                _id;
                uint                _instanceCount;
                bool                _needsUpdate;

                List<PathCommands>  _commands;
                List<float>         _coordinates;
        };
    }
}
