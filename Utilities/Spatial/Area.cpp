/* CHANGELOG
 * Written by Josh Grooms on 20150915
 */

#include "Area.h"
#include "Utilities.h"
#include <sstream>

using std::string;
using std::stringstream;



namespace Cyclone
{
    namespace Utilities
    {
        /** CONSTANT DATA **/
        const Area Area::Empty = Area();
        const Area Area::Unit = Area(0.0f, 0.0f, 1.0f, 1.0f);



        /** CONSTRUCTORS **/
        Area::Area() :
            X(0),
            Y(0),
            Width(0),
            Height(0)
        {

        }
        Area::Area(float x, float y, float width, float height) :
            X(x),
            Y(y),
            Width(width),
            Height(height)
        {

        }



        /** UTILITIES **/
        bool Area::Contains(const Area& other) const
        {
            return ( Left() <= other.Left() && Right() >= other.Right() ) &&
                   ( Bottom() <= other.Bottom() && Top() >= other.Top() );
        }
        bool Area::Contains(const Vector2& point) const
        {
            return ( Left() <= point.X && Right() >= point.X ) &&
                   ( Bottom() <= point.Y && Top() >= point.Y );
        }
        Area& Area::Crop(const Area &keep)
        {
            Bottom( Bottom() > keep.Bottom() ? Bottom() : keep.Bottom() );
            Left( Left() > keep.Left() ? Left() : keep.Left() );
            Right( Right() < keep.Right() ? Right() : keep.Right() );
            Top( Top() < keep.Top() ? Top() : keep.Top() );
            return *this;
        }
        Area& Area::Flip(uint dim)
        {
            if (dim == 1)
            {
                X = Right();
                Width = -Width;
            }
            else
            {
                Y = Top();
                Height = -Height;
            }

            return *this;
        }
        bool Area::Intersects(Area other) const
        {
            Area copy(*this);
            copy.Rectify();
            other.Rectify();

            return  copy.X >= other.Right()  ? false :
                    copy.Right() <= other.X  ? false :
                    copy.Y >= other.Top()    ? false :
                    copy.Top() <= other.Y    ? false :
                    true;
        }
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
        Area& Area::Rectify()
        {
            if (Height < 0)
            {
                Y = Top();
                Height = -Height;
            }
            if (Width < 0)
            {
                X = Right();
                Width = -Width;
            }
            return *this;
        }
        bool Area::Surrounds(const Area &other) const
        {
            return ( Left() < other.Left() && Right() > other.Right() ) &&
                   ( Bottom() < other.Bottom() && Top() > other.Top() );
        }
        Area& Area::Union(const Area& other)
        {
            X = Math::Min(Left(), Right(), other.Left(), other.Right());
            Y = Math::Min(Bottom(), Top(), other.Bottom(), other.Top());

            Right( Math::Max(Left(), Right(), other.Left(), other.Right()) );
            Top( Math::Max(Bottom(), Top(), other.Bottom(), other.Top()) );

            return *this;
        }



        /** OPERATORS **/
        bool Area::operator ==(const Area& other) const
        {
            return X == other.X && Y == other.Y && Width == other.Width && Height == other.Height;
        }
    }
}