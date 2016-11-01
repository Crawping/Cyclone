/* CHANGELOG
 * Written by Josh Grooms on 20161023
 */

#pragma once
#include "Event.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }

    namespace UI
    {
        struct ControlStyle;

        class IInterfaceControl
        {
            public:

                /** PROPERTIES **/
                virtual bool IsEnabled()                const = 0;
                virtual IInterfaceControl* Parent()     const = 0;
                virtual const ControlStyle& Style()     const = 0;
                
                virtual ~IInterfaceControl() { }


                /** UTILITIES **/
                virtual void Configure(const ControlStyle& style) = 0;
        };
    }
}
