/* CHANGELOG
 * Written by Josh Grooms on 20161023
 */

#pragma once
#include "Imaging/Color4.h"
#include "Interfaces/IInterfaceControl.h"
#include "Math/Vector4.h"
#include "Spatial/Area.h"
#include "Spatial/Border.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }

    namespace UI
    {
        class InterfaceControl : public IInterfaceControl
        {
            public:
                
            
                virtual bool IsEnabled()                            const { return _isEnabled; }


                virtual InterfaceControl& IsEnabled(bool value)     { _isEnabled = value; }



            private:
                
                bool        _isEnabled;


        };





        struct ControlStyle
        {
            Color4      BackgroundColor;
            Area        BackgroundArea;
            Color4      BorderColor;
            Border      BorderWidth;
            Border      BorderRadius;
            string      FontName;
            float       FontSize;
            uint        FontWeight;
            Color4      ForegroundColor;
        };
    }
}
