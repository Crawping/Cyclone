#include "Area.h"
#include "Border.h"
#include <sstream>

using std::stringstream;



namespace Cyclone
{
    namespace Utilities
    {
        /** STATIC DATA **/
        const Border Border::Empty = Border();
        const Border Border::Unit = Border(1.0f, 1.0f, 1.0f, 1.0f);



        /** CONSTRUCTORS **/
        Border::Border() :
            Top(0.0f),
            Bottom(0.0f),
            Left(0.0f),
            Right(0.0f)
        {

        }
        Border::Border(float top, float bottom, float left, float right) :
            Top(top),
            Bottom(bottom),
            Left(left),
            Right(right)
        {

        }



        /** UTILITIES **/
        Border& Border::Flip(uint dim)
        {
            if (dim == 1)
                std::swap(Left, Right);
            else
                std::swap(Top, Bottom);
            return *this;
        }
        string Border::Report() const
        {
            stringstream msg;
            msg << "Border Description:"        << "\n" <<
                   "\tTop:      " << Top        << "\n" <<
                   "\tBottom:   " << Bottom     << "\n" <<
                   "\tLeft:     " << Left       << "\n" <<
                   "\tRight:    " << Right      << "\n";
            return msg.str();
        }
    }
}