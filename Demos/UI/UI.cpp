/* CHANGELOG
 * Written by Josh Grooms on 20161022
 */

#include "NVPR.h"
#include "PathRenderer.h"
#include "Controls/Button.h"
#include "Geometry/Rectangle2D.h"

using namespace Renderers;
using namespace Cyclone::SVG;
using namespace Cyclone::UI;


class Program : public PathRenderer
{
    public:

        Program() : 
            PathRenderer(Area(0, 0, 1024, 960), "UI Conceptualization")
        {
            Initialize();
        }
        ~Program()
        {
            for (Button* b : ButtonControls)
                if (b) { delete b; }
        }

    protected:

        Button ButtonControl;
        List<Button*> ButtonControls;

        void CreateSceneResources() override
        {
            PathRenderer::CreateSceneResources();

            for (uint a = 0; a < 20; a++)
            {
                Button* btn = new Button();
                btn->CornerRadius(12.5f)
                    .Size(Vector2(128, 48))
                    .StrokeWidth(0.01f)

                    .Position(0.0f, a * 48.0f, 0.0f)
                    .PrimaryColor(Color4(0.25f, 0.25f, 0.25f, 1.0f))
                    .SecondaryColor(Color4::Transparent);

                ButtonControls.Append(btn);
                PathScene->Add(*btn);
            }




            //ButtonControl
            //    .CornerRadius(12.5f)
            //    .Size(Vector2(256, 50))
            //    .StrokeWidth(0.01f)

            //    .Position(RenderWindow->ClientArea().Center())
            //    .PrimaryColor(Color4(0.25f, 0.25f, 0.25f, 1.0f))
            //    .SecondaryColor(Color4::Transparent);
            //    //.Scale(512, 50);


            //PathScene->Add(ButtonControl);
        }

        void ProcessPointerMotion(const PointerMotionEvent& evt) override
        {
            PathRenderer::ProcessPointerMotion(evt);

            for (Button* btn : ButtonControls)
            {
                if (nvIsPointInFillPath(btn->ID(), ~0, PointerPosition.X, RenderWindow->ClientArea().Height - PointerPosition.Y))
                {
                    btn->PrimaryColor(0.75f);
                    PathScene->Update(*btn);
                }
                else if (btn->PrimaryColor().R == 0.75f)
                {
                    btn->PrimaryColor(0.25f);
                    PathScene->Update(*btn);
                }
            }

            //if (nvIsPointInFillPath(ButtonControl.ID(), ~0, PointerPosition.X, RenderWindow->ClientArea().Height - PointerPosition.Y))
            //    ButtonControl.PrimaryColor(0.75f);
            //else
            //    ButtonControl.PrimaryColor(0.25f);
        }
    
};


int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}