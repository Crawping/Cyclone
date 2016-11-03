#include "NVPR.h"
#include "Buffers/PathBuffer.h"



namespace Cyclone
{
    namespace SVG
    {

        /** CONSTRUCTOR & DESTRUCTOR **/
        PathBuffer::PathBuffer() :
            _id(0),
            _instanceCount(0),
            _needsUpdate(false)
        {

        }
        PathBuffer::~PathBuffer()
        {
            if (_id) { nvDeletePaths(_id, _instanceCount); }
        }



        /** UTILITIES **/
        void PathBuffer::Add(const ControlPoint2D& point)
        {

        }
        void PathBuffer::Add(const ICollection<ControlPoint2D>& points)
        {
            
        }
        void PathBuffer::Clear()
        {

        }
        void PathBuffer::Update()
        {

        }

    }
}