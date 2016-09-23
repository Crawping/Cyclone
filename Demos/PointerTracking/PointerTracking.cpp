/* CHANGELOG
 * Written by Josh Grooms on 20160923
 */

#include "BasicRenderer.h"
#include "Console.h"
#include "Window3D.h"

using namespace Renderers;
using namespace Cyclone::Platform;
using namespace Cyclone::Utilities;

class Program : public BasicRenderer
{
    public: 
        Program() : 
            BasicRenderer("Pointer Tracking")
        {
            Initialize();
        }

        void Execute() override
        {
            while (CanContinue())
                RenderWindow->ProcessEvent();
        }

    protected:
        
        void CreateRenderingWindow() override
        {
            BasicRenderer::CreateRenderingWindow();
            RenderWindow->OnPointerMotion.Register(this, &Program::WhenPointerMoves);
        }

        void Initialize() override
        {
            CreateRenderingWindow();
        }

        void WhenPointerMoves(PointerMotion evt)
        {
            Console::WriteLine("1. Pointer Position:  " + evt.PointerPosition.ToString());
            Console::WriteLine("2. Pointer Delta:     " + evt.PointerPositionDelta.ToString());
            Console::WriteLine("");
        }
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}