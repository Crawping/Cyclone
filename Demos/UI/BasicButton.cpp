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
            PathRenderer(Area(0, 0, 1024, 960), "UI - Basic Button")
        {
            Initialize();
        }
        ~Program()
        {
            for (Button* b : ButtonControls)
                if (b) { delete b; }
        }

    protected:

        List<Button*> ButtonControls;

        void CreateSceneResources() override
        {
            PathRenderer::CreateSceneResources();

            uint nbuttons = 64;
            Vector2 szButton(96.0f, 40.0f);
            Vector2 szButtonArea = RenderWindow->ClientArea().Scale() / 8.0f;
            Vector2 offset = (szButtonArea - szButton) / 2.0f;

            uint a = 0; uint b = 0;
            for (uint a = 0; a < 8; a++)
                for (uint b = 0; b < 8; b++)
                {
                    Button* btn = new Button();
                    Vector2 posButton(a * szButtonArea.X + offset.X, b * szButtonArea.Y + offset.Y);

                    btn->Text("Testing!")
                        .Offset(posButton)
                        .Size(szButton)

                        .BackgroundColor(Color4(0.25f))
                        .BorderColor(Color4(0.0f, 0.0f, 0.0f, 0.75f))
                        .BorderRadius(6.25f)
                        .BorderWidth(2.5f);

                    ButtonControls.Append(btn);
                    PathScene->Add(btn->Shape());
                    PathScene->Add(*(btn->Components().First()));
                }
        }

        void ProcessPointerMotion(const PointerMotionEvent& evt) override
        {
            PathRenderer::ProcessPointerMotion(evt);

            for (Button* btn : ButtonControls)
            {
                if (nvIsPointInFillPath(btn->Shape().ID(), ~0, PointerPosition.X, RenderWindow->ClientArea().Height - PointerPosition.Y))
                {
                    if (btn->BackgroundColor().R == 0.25f)
                    {
                        btn->BackgroundColor(Color4::Random());
                        PathScene->Update(btn->Shape());
                    }
                }
                else if (btn->BackgroundColor().R != 0.25f)
                {
                    btn->BackgroundColor(0.25f);
                    PathScene->Update(btn->Shape());
                }
            }
        }
    
};


int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}