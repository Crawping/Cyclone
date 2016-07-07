#include "Volume.h"
#include <sstream>



/** CONSTANT DATA **/
const Volume Volume::Empty  = Volume(Vector3::Zero, Vector3::Zero);
const Volume Volume::Unit   = Volume();



/** UTILITIES **/
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
