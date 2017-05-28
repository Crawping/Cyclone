/* CHANGELOG
 * Written by Josh Grooms on 20160914
 */

#include "BasicRenderer.h"
#include "GPU.h"
#include "Collections/List.h"
#include "IO/Console.h"
using namespace Renderers;



class Program : public BasicRenderer
{
    public: 
        Program() : BasicRenderer(Area(0, 0, 1, 1), "OpenGL Extension Support")
        {
            Initialize();

            List<string> exts = Renderer->QueryExtensions();
            for (uint a = 0; a < exts.Count(); a++)
                Console::WriteLine(exts(a));
        }
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}