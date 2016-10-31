/* CHANGELOG
 * Written by Josh Grooms on 20161030
 */

#pragma once
#include "UIAPI.h"
#include "Controls/InterfaceControl.h"



namespace Cyclone
{
    namespace UI
    {
        class Panel : public InterfaceControl
        {
            public:
            
                UIAPI Panel();



                UIAPI void Configure(const ControlStyle& style) override;

            
                
            protected:


        };
    }
}
