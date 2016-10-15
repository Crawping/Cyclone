/* CHANGELOG 
 * Written by Josh Grooms on 20161008
 */

#include "Console.h"
#include "PathRenderer.h"
#include "NVPR.h"
#include "Geometry/DrawingPath.h"
#include "Spatial/Transform.h"

using namespace Renderers;
using namespace Cyclone::SVG;
using namespace Cyclone::Utilities;



class Program : public PathRenderer
{
    public:
        
        Program() : 
            PathRenderer(Area(0, 0, 1024, 960), "Picking SVG Elements"),
            IsShapeMoving(false)
        {
            RenderWindow->OnButtonPress.Register(this, &Program::ProcessButtonPress);
            RenderWindow->OnButtonRelease.Register(this, &Program::ProcessButtonRelease);

            Initialize();

            glEnable(GL_CULL_FACE);
        }



    protected:
        DrawingPath     Path;
        bool            IsShapeMoving;


        void CreateSceneResources() override
        {
            PathRenderer::CreateSceneResources();

            Path
                .JoinStyle(JoinStyles::Round)
                .StrokeColor(Color4(1.0f, 0.0f, 0.0f, 0.875f))
                .StrokeWidth(4)

                .Color(Color4(0.0f, 0.0f, 1.0f, 0.75f));

            PathScene->Add(Path);
        }

        void ProcessButtonPress(const PointerClickEvent& evt)
        {
            if (evt.Button == PointerButtons::Button001)
            {
                if (Path.Color() == Color4::Green)
                    IsShapeMoving = true;
                else
                {
                    ControlPoint2D newPt =
                    {
                        PathCommands::Line,
                        { PointerPosition.X, RenderWindow->ClientArea().Height - PointerPosition.Y }
                    };

                    if (Path.IsEmpty() || Path.IsClosed())
                        newPt.Command = PathCommands::Move;

                    Path.Add(newPt);
                }
            }
            else if (evt.Button == PointerButtons::Button003)
                IsFreeLookEnabled = true;
        }
        void ProcessButtonRelease(const PointerClickEvent& evt)
        {
            if (evt.Button == PointerButtons::Button001)
                IsShapeMoving = false;
            if (evt.Button == PointerButtons::Button003)
                IsFreeLookEnabled = false;
        }

        void ProcessKeyPress(const KeyboardEvent& evt) override
        {
            if (evt.Key == KeyboardKeys::C)
                Path.Add
                ({
                    PathCommands::SmoothQuadraticCurve,
                    {
                        PointerPosition.X,
                        RenderWindow->ClientArea().Height - PointerPosition.Y,
                    }
                });

            else if (evt.Key == KeyboardKeys::E)
                Path.Add({ PathCommands::Close, { } });
            else if (evt.Key == KeyboardKeys::F2)
                Path.Clear();

            PathRenderer::ProcessKeyPress(evt);
        }
        void ProcessPointerMotion(const PointerMotionEvent& evt) override
        {
            PathRenderer::ProcessPointerMotion(evt);

            if (IsShapeMoving)
            {
                float translation[3] = { evt.Delta.X, -evt.Delta.Y, 0.0f };
                nvTransformPath(Path.ID(), Path.ID(), TransformTypes::Translate3D, translation);
            }

            if (nvIsPointInFillPath(Path.ID(), ~0, PointerPosition.X, RenderWindow->ClientArea().Height - PointerPosition.Y))
                Path.Color(Color4::Green);
            else
                Path.Color(Color4::Blue);
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}