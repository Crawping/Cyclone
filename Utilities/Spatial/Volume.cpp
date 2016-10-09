#include "Volume.h"
#include <sstream>


//namespace Cyclone::Utilities
//{
namespace Cyclone
{
    namespace Utilities
    {

        /** CONSTANT DATA **/
        const Volume Volume::Empty  = Volume(Vector3::Zero, Vector3::Zero);
        const Volume Volume::Unit   = Volume();



        /** UTILITIES **/
        constexpr bool Volume::Contains(const Vector3& point) const
        {
            return
                (Left() <= point.X && Right() >= point.X) &&
                (Bottom() <= point.Y && Top() >= point.Y) &&
                (Back() <= point.Z && Front() >= point.Z);
        }
        constexpr bool Volume::Contains(const Volume& volume) const
        {
            return
                (Left() <= volume.Left() && Right() >= volume.Right()) &&
                (Bottom() <= volume.Bottom() && Top() >= volume.Top()) &&
                (Back() <= volume.Back() && Front() >= volume.Front());
        }
        string Volume::Report() const
        {
            std::stringstream msg;
            msg << "Area Description:"          << "\n" <<
                   "\tX:        " << X          << "\n" <<
                   "\tY:        " << Y          << "\n" <<
                   "\tZ:        " << Z          << "\n" <<
                   "\tWidth:    " << Width      << "\n" <<
                   "\tHeight:   " << Height     << "\n" <<
                   "\tDepth:    " << Depth      << "\n\n" <<

                   "\tLeft:     " << Left()     << "\n" <<
                   "\tRight:    " << Right()    << "\n" <<
                   "\tTop:      " << Top()      << "\n" <<
                   "\tBottom:   " << Bottom()   << "\n" <<
                   "\tFront:    " << Front()    << "\n" <<
                   "\tBack:     " << Back()     << "\n";

            return msg.str();
        }

    }
}