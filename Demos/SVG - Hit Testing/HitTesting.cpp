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
            Offset(0.0f),
            WorkingPath(nullptr),
            IsShapeMoving(false)
        {
            RenderWindow->OnButtonPress.Register(this, &Program::ProcessButtonPress);
            RenderWindow->OnButtonRelease.Register(this, &Program::ProcessButtonRelease);

            Initialize();
        }
        ~Program()
        {
            for (DrawingPath* p : Paths)
                delete p;
        }



    protected:
        
        float               Offset;
        List<DrawingPath*>  Paths;
        DrawingPath*        WorkingPath;
        bool                IsShapeMoving;


        void Insert(PathCommands cmd, Vector<float> parameters)
        {
            WorkingPath->Append({ cmd, parameters });
        }

        void CreateWorkingPath()
        {
            if (WorkingPath)
                Insert(PathCommands::Close, { });

            WorkingPath = new DrawingPath();
            WorkingPath->
                 PointColor(Color4::Black)
                .PointSize(10)

                .TerminalCap(EndCaps::Triangular)
                .InitialCap(EndCaps::Triangular)
                .JoinStyle(JoinStyles::Round)
                .StrokeWidth(2)

                .PrimaryColor(Color4(0.0f, 0.0f, 1.0f, 0.75f))
                .SecondaryColor(Color4(1.0f, 0.0f, 0.0f, 0.875f))
                .Z(Offset);

            Offset += 0.01f;

            PathScene->Insert(*WorkingPath);
            Paths.Append(WorkingPath);
        }
        void CreateSceneResources() override
        {
            PathRenderer::CreateSceneResources();
            CreateWorkingPath();
        }
        void ProcessButtonPress(const PointerClickEvent& evt)
        {
            if (evt.Button == PointerButtons::Button001)
            {
                if (WorkingPath->PrimaryColor() == Color4::Green)
                    IsShapeMoving = true;
                else
                {
                    Vector2 pt = CalculatePointerInWorld(-PointerWorldRay(0).Z);
                    PathCommands cmd = ( WorkingPath->IsEmpty() || WorkingPath->IsClosed() ) ? PathCommands::Move : PathCommands::Line;
                    Insert(cmd, { pt.X, pt.Y });
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
            {
                //Vector2 pt = GetSurfacePoint(Vector2(PointerPosition));
                Vector2 pt = CalculatePointerInWorld(-PointerWorldRay(0).Z);
                Insert(PathCommands::SmoothQuadraticCurve, { pt.X, pt.Y });
            }
            else if (evt.Key == KeyboardKeys::E)
                CreateWorkingPath();
            else if (evt.Key == KeyboardKeys::F2)
            {
                PathScene->Remove(*WorkingPath);
                WorkingPath->Clear();
            }

            PathRenderer::ProcessKeyPress(evt);
        }
        void ProcessPointerMotion(const PointerMotionEvent& evt) override
        {
            PathRenderer::ProcessPointerMotion(evt);

            Vector2 pt = CalculatePointerInWorld(-PointerWorldRay(0).Z);
            for (auto* p : Paths)
                if (nvIsPointInFillPath(p->ID(), ~0, pt.X, pt.Y))
                {
                    p->PrimaryColor(Color4::Green);
                    break;
                }
                else if (p->PrimaryColor() == Color4::Green)
                    p->PrimaryColor(Color4::Blue);
        }
        void UpdateScene() override
        {
            for (auto* p : Paths)
                PathScene->Update(*p);
            PathRenderer::UpdateScene();
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}