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
            _id = nvGenPaths(count);
        }
        PathBuffer::~PathBuffer()
        {
            if (_id) { nvDeletePaths(_id, _instanceCount); }
        }



        /** BUFFER UTILITIES **/
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
        PathBuffer& PathBuffer::Remove(uint index)
        {
            if (index >= Count()) { return *this; }
            Data.Remove(index);
            NeedsUpdate(true);
            return *this;
        }
        PathBuffer& PathBuffer::Set(uint index, const ControlPoint2D& point)
        {
            if (index == Count())
                return Add(point);
            else
                Data(index) = point;

            NeedsUpdate(true);
            return *this;
        }
        void PathBuffer::Update()
        {
            if (!_needsUpdate) { return; }

            auto cmds = Commands().ToVector();
            auto crds = Coordinates().ToVector();

            nvPathCommands
            (
                ID(),
                cmds.Count(),
                (const ubyte*)(cmds.ToArray()),
                crds.Count(),
                NumericFormats::Float,
                crds.ToArray()
            );

            _needsUpdate = false;
        }
        void PathBuffer::Update() const
        {
            if (!_needsUpdate) { return; }

            auto cmds = Commands().ToVector();
            auto crds = Coordinates().ToVector();

            nvPathCommands
            (
                ID(),
                cmds.Count(),
                (const ubyte*)(cmds.ToArray()),
                crds.Count(),
                NumericFormats::Float,
                crds.ToArray()
            );

            _needsUpdate = false;
        }
    }
}