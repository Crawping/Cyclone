/* CHANGELOG 
 * Written by Josh Grooms on 20161002
 */

#include "GPU.h"
#include "NVPR.h"
#include "PathRenderer.h"
#include "Window3D.h"
#include "Geometry/DrawingPath.h"
#include "Geometry/Quad3D.h"
#include "Geometry/Scene3D.h"
#include "Geometry/Path2D.h"
#include "Pipelines/ShaderPipeline.h"
#include "Text/Text2D.h"
#include "Textures/Texture2D.h"

using namespace Renderers;
using namespace Cyclone::OpenGL;
using namespace Cyclone::SVG;
using namespace Cyclone::Platform;
using namespace Cyclone::Utilities;



class Program : public PathRenderer
{
    public:

        Program() : 
            PathRenderer(Area(0, 0, 1024, 960), "Drawing SVG Elements"),
            Image(nullptr),
            IsEnteringText(false)
        {
            Initialize();

            RenderWindow->OnButtonPress.Register(this, &Program::ProcessButtonPress);
            RenderWindow->OnButtonRelease.Register(this, &Program::ProcessButtonRelease);

            nvPathStencilDepthOffset(-0.05f, -1);
            nvPathCoverDepthFunc(GL_ALWAYS);

			glEnable(GL_CULL_FACE);
        }
        ~Program()
        {
            for (uint a = 0; a < TextBoxes.Count(); a++)
                delete TextBoxes(a);

            if (Image)          { delete Image; }
        }

    protected:
        DrawingPath         Path;
        Texture2D*          Image;
        bool                IsEnteringText;
        Vector2             LastClickPosition;
        Quad3D              Quad;
        List<Text2D*>       TextBoxes;



        void CreateSceneResources() override
        {
            PathRenderer::CreateSceneResources();

            Image = new Texture2D("../ImageDisplay/House (11250x8627).jpg");
            Image->Bind();

            Quad
                .Position(RenderWindow->ClientArea().Scale() / 2.0f)
                .Scale(Vector3(RenderWindow->ClientArea().Scale(), 0.0f));

            Path
                .JoinStyle(JoinStyles::Round)
                .StrokeWidth(2)
                .PrimaryColor(Color4(0.0f, 0.0f, 1.0f, 0.75f))
                .SecondaryColor(Color4(1.0f, 0.0f, 0.0f, 0.875f));

            RenderScene->Add(Quad);
            PathScene->Add(Path);
        }
        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../ImageDisplay/TexturedShading.psl");
            PipelineSVG = new ShaderPipeline("../Renderers/Shaders/SVG.psl");
        }



        void ProcessButtonPress(const PointerClickEvent& evt)
        {
            if (evt.Button == PointerButtons::Button001)
            {
                LastClickPosition = PointerPosition;
                ControlPoint2D newPt =
                {
                    PathCommands::Line,
                    { PointerPosition.X, RenderWindow->ClientArea().Height - PointerPosition.Y }
                };

                if (Path.IsEmpty() || Path.IsClosed())
                    newPt.Command = PathCommands::Move;

                Path.Add(newPt);
            }
            else if (evt.Button == PointerButtons::Button003)
                IsFreeLookEnabled = true;
        }
        void ProcessButtonRelease(const PointerClickEvent& evt)
        {
            if (evt.Button == PointerButtons::Button003)
                IsFreeLookEnabled = false;
        }

        void ProcessKeyPress(const KeyboardEvent& evt) override
        {
            if (evt.Key == KeyboardKeys::Enter && IsEnteringText)
            {
                IsEnteringText = false;
                return;
            }

            if (IsEnteringText)
            {
                Text2D* text = TextBoxes.Last();
                text->Text(text->Text() + (char)(evt.Code));
                return;
            }
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
            else if (evt.Key == KeyboardKeys::T)
            {
                IsEnteringText = true;
                CreateTextBox();
                return;
            }
            else if (evt.Key == KeyboardKeys::F2)
            {
                for (uint a = 0; a < TextBoxes.Count(); a++)
                {
                    PathScene->Remove(*TextBoxes(a));
                    delete TextBoxes(a);
                }

                TextBoxes.Clear();
                Path.Clear();
                PathScene->Update(Path);
            }

            AdvancedRenderer::ProcessKeyPress(evt);
        }



        void UpdateScene() override
        {
            RenderScene->Update(Quad);
            PathScene->Update(Path);

            PathRenderer::UpdateScene();
        }
        

    private:

        void CreateTextBox()
        {
            Text2D* text = new Text2D();
            text->
                 PrimaryColor(Color4::Yellow)
                .Scale(0.0125f, 0.0125f)
                .Position(PointerPosition.X, RenderWindow->ClientArea().Height - PointerPosition.Y);

            TextBoxes.Append(text);
            PathScene->Add(*text);
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}