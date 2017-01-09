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
            Vector3 szPanel = RenderWindow->ClientArea().Scale() / 2.0f;

            PanelControl
                .BackgroundColor(Color4(0.25f))
                .BorderColor(Color4(0.75f, 0.75f, 0.75f, 0.375f))
                .BorderRadius(12.5f)
                .BorderWidth(10)
                .Offset(szPanel)
                .Size(szPanel);

            PanelControl.Update();
            PathScene->Insert(PanelControl.Shape());
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}