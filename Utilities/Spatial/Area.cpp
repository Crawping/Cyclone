/* CHANGELOG
 * Written by Josh Grooms on 20150915
 */

#include "Math/Math.h"
#include "Spatial/Area.h"
#include <sstream>

using std::string;
using std::stringstream;



namespace Cyclone
{
    namespace Utilities
    {
        /** CONSTANT DATA **/
        const Area Area::Empty  = Area(0.0f, 0.0f, 0.0f, 0.0f);
        const Area Area::Unit   = Area(0.0f, 0.0f, 1.0f, 1.0f);



        /** UTILITIES **/
        Area& Area::Normalize()
        {
            float s = 1.0f / (Width > Height ? Width : Height);
            X *= s;
            Y *= s;
            Width *= s;
            Height *= s;
            return *this;
        }
        std::string Area::Report() const
        {
            stringstream msg;
            msg << "Area Description:"          << "\n" <<
                   "\tX:        " << X          << "\n" <<
                   "\tY:        " << Y          << "\n" <<
                   "\tWidth:    " << Width      << "\n" <<
                   "\tHeight:   " << Height     << "\n" <<
                                                   "\n" <<
                   "\tBottom:   " << Bottom()   << "\n" <<
                   "\tLeft:     " << Left()     << "\n" <<
                   "\tRight:    " << Right()    << "\n" <<
                   "\tTop:      " << Top()      << "\n";

            return msg.str();
        }

    }
}