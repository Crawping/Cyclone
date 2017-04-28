/* CHANGELOG
 * Written by Josh Grooms on 20161030
 */

#pragma once



namespace Cyclone
{
    namespace Platform
    {
        struct PointerMotionEvent;
        struct PointerButtonEvent;
        struct KeyboardEvent;
    }

    namespace UI
    {
        namespace { using namespace Platform; }

        class IInteractive
        {
            public:


                virtual ~IInteractive() { }


                /** EVENT HANDLERS **/
                virtual void ProcessButtonPress(IInteractive& src, const PointerButtonEvent& evt)   = 0;
                virtual void ProcessButtonRelease(IInteractive& src, const PointerButtonEvent& evt) = 0;
                virtual void ProcessKeyPress(IInteractive& src, const KeyboardEvent& evt)           = 0;
                virtual void ProcessKeyRelease(IInteractive& src, const KeyboardEvent& evt)         = 0;
                virtual void ProcessPointerMotion(IInteractive& src, const PointerMotionEvent& evt) = 0;
        };
    }
}
