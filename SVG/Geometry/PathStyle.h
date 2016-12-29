/* CHANGELOG 
 * Written by Josh Grooms on 20161102
 */

#pragma once
#include "EnumerationsSVG.h"
#include "Imaging/Color4.h"



namespace Cyclone
{
    namespace SVG
    {
        struct PathStyle
        {

            /** DATA **/
            CoverModes          CoverMode;
            FillModes           FillMode;
            EndCaps             InitialCap;
            JoinStyles          JoinStyle;
            float               StrokeWidth;
            EndCaps             TerminalCap;



            /** CONSTRUCTOR **/
            PathStyle() :
                StrokeWidth(1.0f)
            {

            }

        };
    }
}
