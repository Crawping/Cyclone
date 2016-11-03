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
                uint ID()           const { return _id; }
                bool IsClosed()     const { return !_commands.IsEmpty() && (_commands.Last() == PathCommands::Close); }


                
                /** CONSTRUCTOR & DESTRUCTOR **/
                SVGAPI PathBuffer();
                SVGAPI ~PathBuffer();


                SVGAPI void Add(const ControlPoint2D& point);
                SVGAPI void Add(const ICollection<ControlPoint2D>& points);
                SVGAPI void Clear();
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
