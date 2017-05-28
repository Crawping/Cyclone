/* CHANGELOG
 * Written by Josh Grooms on 20160923
 */

#include "BasicRenderer.h"
#include "Window3D.h"
#include "IO/Console.h"

using namespace Renderers;
using namespace Cyclone::Platform;
using namespace Cyclone::Utilities;

class Program : public BasicRenderer
{
    public: 
        Program() : 
            BasicRenderer(Area(0, 0, 1024, 960), "Pointer Tracking")
        {
			RenderWindow->OnPointerMotion.Register(this, &Program::WhenPointerMoves);
			RenderWindow->OnButtonPress.Register(this, &Program::WhenButtonPresses);
			RenderWindow->OnButtonRelease.Register(this, &Program::WhenButtonReleases);

            Initialize();
        }

        void Execute() override
        {
            while (CanContinue())
                RenderWindow->ProcessEvent();
        }

    protected:

        void Initialize() override { }

        void WhenPointerMoves(const PointerMotionEvent& evt)
        {
            Console::WriteLine("1. Pointer Position:    " + evt.Position.ToString());
            Console::WriteLine("2. Pointer Delta:       " + evt.Delta.ToString());
            Console::WriteLine("");
        }
        void WhenButtonPresses(const PointerClickEvent& evt)
        {
            Console::WriteLine("1. Button Pressed:      " + evt.Button.ToString());
            Console::WriteLine("2. " + evt.State.Report());
            Console::WriteLine("");
        }
        void WhenButtonReleases(const PointerClickEvent& evt)
        {
            Console::WriteLine("1. Button Released:     " + evt.Button.ToString());
            Console::WriteLine("2. " + evt.State.Report());
            Console::WriteLine("");
        }
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}