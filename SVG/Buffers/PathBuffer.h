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
                /// <summary> Gets the number of individual control points stored within the buffer. </summary>
                uint Count()            const override { return Data.Count(); }
                /// <summary> Gets the unique numeric identifier for the path object on the GPU. </summary>
                uint ID()               const { return _id; }
                /// <summary> Gets the number of individual path instances that have been allocated on the GPU. </summary>
                /// <remarks>
                ///     For almost all imaging-related paths, this property will return a value of <c>1</c>. Values greater
                ///     than <c>1</c> indicate the number of times that a path object is being instanced on the GPU, which
                ///     is almost exclusively used only by text rendering.
                /// </remarks>
                uint InstanceCount()    const { return _instanceCount; }
                /// <summary> Gets whether the path object has been terminated by a close command. </summary>
                bool IsClosed()         const { return !Data.IsEmpty() && (Data.Last().Command == PathCommands::Close); }
                bool NeedsUpdate()      const override { return _needsUpdate; }

                SVGAPI List<PathCommands> Commands() const;
                SVGAPI List<float> Coordinates() const;

                

                /** CONSTRUCTOR & DESTRUCTOR **/
                SVGAPI PathBuffer(uint count = 1);
                SVGAPI ~PathBuffer();



                /** UTILITIES **/
                SVGAPI PathBuffer& Add(const ControlPoint2D& point);
                SVGAPI PathBuffer& Add(const ICollection<ControlPoint2D>& points);
                SVGAPI void Clear() override;
                SVGAPI PathBuffer& Remove(uint index);
                SVGAPI PathBuffer& Set(uint index, const ControlPoint2D& point);
                /// <summary> Transfers all application-side data within the buffer over to its corresponding GPU storage. </summary>
                SVGAPI void Update() override;
                SVGAPI void Update() const;



                const ControlPoint2D& operator ()(uint index) const { return Data(index); }


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
