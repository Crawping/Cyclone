#include "Entity2D.h"



namespace Cyclone
{
    namespace SVG
    {
        
        /** PROPERTIES **/
        Entity2D& Entity2D::CoverMode(CoverModes value)
        {
            _style.CoverMode = value;
            return *this;
        }
        Entity2D& Entity2D::FillMode(FillModes value)
        {
            _style.FillMode = value;
            return *this;
        }
        Entity2D& Entity2D::InitialCap(EndCaps value)
        {
            _style.InitialCap = value;
            return *this;
        }
        Entity2D& Entity2D::JoinStyle(JoinStyles value)
        {
            _style.JoinStyle = value;
            return *this;
        }
        Entity2D& Entity2D::StrokeWidth(float value)
        {
            _style.StrokeWidth = value;
            return *this;
        }
        Entity2D& Entity2D::Style(const PathStyle& value)
        {
            return
                 CoverMode(value.CoverMode)
                .FillMode(value.FillMode)
                .InitialCap(value.InitialCap)
                .JoinStyle(value.JoinStyle)
                .StrokeWidth(value.StrokeWidth)
                .TerminalCap(value.TerminalCap);
        }
        Entity2D& Entity2D::TerminalCap(EndCaps value)
        {
            _style.TerminalCap = value;
            return *this;
        }

    }
}

