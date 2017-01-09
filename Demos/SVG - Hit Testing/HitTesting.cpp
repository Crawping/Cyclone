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

            //glEnable(GL_CULL_FACE);
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
                    Vector2 pt = GetSurfacePoint(Vector2(PointerPosition));
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
                Vector2 pt = GetSurfacePoint(Vector2(PointerPosition));
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

            Vector2 pt = GetSurfacePoint(evt.Position);
            for (auto* p : Paths)
                if (nvIsPointInFillPath(p->ID(), ~0, pt.X, pt.Y))
                {
                    p->PrimaryColor(Color4::Green);
                    break;
                }
                else if (p->PrimaryColor() == Color4::Green)
                    p->PrimaryColor(Color4::Blue);
        }

        Vector2 GetSurfacePoint(const Vector2& point)
        {
            Area clArea(RenderWindow->ClientArea());
            Matrix4x4 invViewProj = (Projection.ToMatrix4x4() * View.ToMatrix4x4()).Inverse();

            Vector4 pt1 = Vector4(point.X, clArea.Height - point.Y, -1, 1);
            pt1.X = (2.0f * pt1.X / clArea.Width) - 1.0f;
            pt1.Y = (2.0f * pt1.Y / clArea.Height) - 1.0f;

            Vector4 pt2 = pt1;
            pt2.Z = -pt1.Z;

            pt1 = invViewProj * pt1;
            pt2 = invViewProj * pt2;

            pt1 /= pt1.W;
            pt2 /= pt2.W;

            float scale = -pt1.Z / (pt2.Z - pt1.Z);
            return Vector2(scale * (pt2.X - pt1.X) + pt1.X, scale * (pt2.Y - pt1.Y) + pt1.Y);
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