#include "EnumerationsGL.h"
#include "NVPR.h"
#include "Buffers/PathBuffer.h"



namespace Cyclone
{
    namespace SVG
    {
        /** PROPERTIES **/
        List<PathCommands> PathBuffer::Commands() const
        {
            List<PathCommands> output;
            for (const ControlPoint2D& p : Data)
                output.Append(p.Command);
            return output;
        }
        List<float> PathBuffer::Coordinates() const
        {
            List<float> output;
            for (const ControlPoint2D& p : Data)
                output.Append(p.Coordinates);
            return output;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        PathBuffer::PathBuffer(uint count) :
            _id(0),
            _instanceCount(count),
            _needsUpdate(false)
        {

        }
        PathBuffer::~PathBuffer()
        {
            if (_id) { nvDeletePaths(_id, _instanceCount); }
        }



        /** UTILITIES **/
        PathBuffer& PathBuffer::Add(const ControlPoint2D& point)
        {
            Data.Append(point);
            NeedsUpdate(true);
            return *this;
        }
        PathBuffer& PathBuffer::Add(const ICollection<ControlPoint2D>& points)
        {
            for (uint a = 0; a < points.Count(); a++)
                Add(points(a));
            return *this;
        }
        void PathBuffer::Clear()
        {
            Data.Clear();
            NeedsUpdate(true);
        }
        void PathBuffer::Update()
        {
            if (!_needsUpdate) { return; }

            auto cmds = Commands().ToVector();
            auto coords = Coordinates().ToVector();

            nvPathCommands
            (
                ID(),
                cmds.Count(),
                (const ubyte*)(cmds.ToArray()),
                coords.Count(),
                NumericFormats::Float,
                coords.ToArray()
            );

            _needsUpdate = false;
        }

    }
}