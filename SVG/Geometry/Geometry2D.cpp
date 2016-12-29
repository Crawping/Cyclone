#include "Geometry/Geometry2D.h"



namespace Cyclone
{
    namespace SVG
    {

        Vector<PathCommands> GeometrySVG::Commands() const
        {
            Vector<PathCommands> cmds = Vector<PathCommands>(ControlPoints.Count());
            for (uint a = 0; a < ControlPoints.Count(); a++)
                cmds(a) = ControlPoints(a).Command;
            return cmds;
        }
        bool GeometrySVG::IsClosed() const
        {
            return !IsEmpty() && ControlPoints.Last().Command == PathCommands::Close;
        }
        bool GeometrySVG::IsEmpty() const
        {
            return ControlPoints.IsEmpty();
        }
        Vector<float> GeometrySVG::Parameters() const
        {
            Vector<float> params;
            for (uint a = 0; a < ControlPoints.Count(); a++)
                params.Append(ControlPoints(a).Coordinates);
            return params;
        }


        Vector<ControlPoint2D> Geometry2D::Line()
        {
            return
            {
                { PathCommands::Move,   { -0.5f, 0.0f } },
                { PathCommands::Line,   {  0.5f, 0.0f } },
                { PathCommands::Close,  { } },
            };
        }

        Vector<ControlPoint2D> Geometry2D::Point()
        {
            return
            {
                { PathCommands::Move,   { 0.5f, 0.0f } },
                { PathCommands::Arc,    { 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, -0.5f, 0.0f } },
                { PathCommands::Arc,    { 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  0.5f, 0.0f } },
                { PathCommands::Close,  { } },
            };
        }
        Vector<ControlPoint2D> Geometry2D::Rectangle()
        {
            return
            {
                { PathCommands::Rectangle,  { -0.5f, -0.5f, 1.0f, 1.0f } },
                { PathCommands::Close,      { } },
            };
        }

        Vector<ControlPoint2D> Geometry2D::RoundedRectangle()
        {
            return
            {
                { PathCommands::RoundedRectangle,   { -0.5f, -0.5f, 1.0f, 1.0f, 0.25f } },
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
