/* CHANGELOG 
 * Written by Josh Grooms on 20161104
 */

#include "PathRenderer.h"
#include "Controls/Panel.h"

using namespace Renderers;
using namespace Cyclone::UI;



class Program : public PathRenderer
{
    public:

        Program() : 
            PathRenderer(Area(0, 0, 1024, 960), "UI - Basic Panel")
        {
            Initialize();
        }
        ~Program()
        {

        }
        
    protected:

        Panel PanelControl;


        void CreateSceneResources() override
        {
            PathRenderer::CreateSceneResources();

            PanelControl
                .BackgroundColor(Color4(0.25f))
                .BorderColor(0.125f)
                .BorderRadius(12.5f)
                .Offset(25.0f)
                .Size(RenderWindow->ClientArea().Scale() - 50.0f);

            PathScene->Add(PanelControl.Shape());
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}