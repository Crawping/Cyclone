/* CHANGELOG
 * Written by Josh Grooms on 20160914
 */

#include "BasicRenderer.h"
#include "Console.h"
#include "GPU.h"
#include "Collections/List.h"
using namespace Renderers;



class Program : public BasicRenderer
{
    public: 
        Program() : BasicRenderer("OpenGL Extension Support")
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