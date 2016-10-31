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
        class IInterfaceControl
        {
            public:

                /** PROPERTIES **/
                virtual bool IsEnabled()                const = 0;
                virtual IInterfaceControl* Parent()     const = 0;
                
                virtual ~IInterfaceControl() { }
        };
    }
}
