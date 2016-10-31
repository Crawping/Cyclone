/* CHANGELOG
 * Written by Josh Grooms on 20161030
 */

#pragma once



namespace Cyclone
{
    namespace UI
    {

        class IInteractive
        {
            public:
                
                
                virtual ~IInteractive() { }


                /** EVENT HANDLERS **/
                virtual void ProcessButtonPress()   = 0;
                virtual void ProcessButtonRelease() = 0;
                virtual void ProcessKeyPress()      = 0;
                virtual void ProcessKeyRelease()    = 0;
                virtual void ProcessPointerHover()  = 0;
        };
    }
}