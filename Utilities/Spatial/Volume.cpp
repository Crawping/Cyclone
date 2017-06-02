#include "Math/Math.h"
#include "Spatial/Volume.h"
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
            auto v1 = Rectify(), v2 = volume.Rectify();
            return
                v1.Left() <= v2.Left() && v1.Right() >= v2.Right() &&
                v1.Bottom() <= v2.Bottom() && v1.Top() >= v2.Top() &&
                v1.Back() <= v2.Back() && v1.Front() >= v2.Front();
        }
        constexpr bool Volume::Intersects(const Volume& volume) const
        {
            auto v1 = Rectify();
            auto v2 = volume.Rectify();
            return
                v1.Left() <= v2.Right() && v1.Right() >= v2.Left() &&
                v1.Bottom() <= v2.Top() && v1.Top() >= v1.Bottom() &&
                v1.Back() <= v2.Front() && v1.Front() >= v2.Back();
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