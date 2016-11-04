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
                uint Count()            const override { return Data.Count(); }
                uint ID()               const { return _id; }
                uint InstanceCount()    const { return _instanceCount; }
                bool IsClosed()         const { return !Data.IsEmpty() && (Data.Last().Command == PathCommands::Close); }

                SVGAPI List<PathCommands> Commands() const;
                SVGAPI List<float> Coordinates() const;

                

                /** CONSTRUCTOR & DESTRUCTOR **/
                SVGAPI PathBuffer(uint count = 1);
                SVGAPI ~PathBuffer();


                SVGAPI PathBuffer& Add(const ControlPoint2D& point);
                SVGAPI PathBuffer& Add(const ICollection<ControlPoint2D>& points);
                SVGAPI void Clear();
                SVGAPI void Update();


            protected:

                /** PROPERTIES **/
                void NeedsUpdate(bool value) const { _needsUpdate = _needsUpdate ? true : value; }
                
            private:

                uint                _id;
                uint                _instanceCount;
                mutable bool        _needsUpdate;

                List<ControlPoint2D> Data;

        };
    }
}
