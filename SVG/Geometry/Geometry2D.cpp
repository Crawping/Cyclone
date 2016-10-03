#include "Geometry/Geometry2D.h"



namespace Cyclone
{
    namespace SVG
    {

        Vector<ControlPoint2D> Geometry2D::Line()
        {
            return
            {
                { PathCommands::Move,   { -0.5, 0 } },
                { PathCommands::Line,   {  0.5, 0 } },
                { PathCommands::Close,  { } },
            };
        }

        Vector<ControlPoint2D> Geometry2D::Rectangle()
        {
            return 
            {
                { PathCommands::Rectangle,  { 0, 0, 100, 100 } },
                { PathCommands::Close,      { } },
            };
        }

        Vector<ControlPoint2D> Geometry2D::RoundedRectangle()
        {
            return
            {
                { PathCommands::RoundedRectangle,   { 0, 0, 100, 100, 12 } },
                { PathCommands::Close,              { } },
            };
        }

        Vector<ControlPoint2D> Geometry2D::Star()
        {
            return
            {
                { PathCommands::Move,   {  40,  10 } },
                { PathCommands::Line,   { 100, 180 } },
                { PathCommands::Line,   { 160,  10 } },
                { PathCommands::Line,   {  10, 120 } },
                { PathCommands::Line,   { 190, 120 } },
                { PathCommands::Close,  { } },
            };
        }
    }
}