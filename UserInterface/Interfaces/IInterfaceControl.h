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
                virtual bool IsEnabled() const = 0;



                /** EVENT HANDLERS **/
                virtual void ProcessButtonPress()   = 0;
                virtual void ProcessButtonRelease() = 0;
                virtual void ProcessKeyPress()      = 0;
                virtual void ProcessKeyRelease()    = 0;
                virtual void ProcessPointerHover()  = 0;


                
                virtual ~IInterfaceControl() { }
        };
    }
}
