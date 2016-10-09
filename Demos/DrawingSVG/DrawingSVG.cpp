/* CHANGELOG 
 * Written by Josh Grooms on 20161002
 */

#include "AdvancedRenderer.h"
#include "GPU.h"
#include "NVPR.h"
#include "Window3D.h"
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



class Program : public AdvancedRenderer
{
    public:

        Program() : 
            AdvancedRenderer(Area(0, 0, 1024, 960), "Drawing SVG Elements", 4),
            Image(nullptr),
            IsEnteringText(false),
            PipelineSVG(nullptr),
            SceneSVG(nullptr)
        {
            IsFreeLookEnabled = false;
            RenderWindow->OnButtonPress.Register(this, &Program::ProcessButtonPress);
            RenderWindow->OnButtonRelease.Register(this, &Program::ProcessButtonRelease);
            Initialize();

            nvPathStencilDepthOffset(-0.05f, -1);
            nvPathCoverDepthFunc(GL_ALWAYS);

			glEnable(GL_CULL_FACE);
        }
        ~Program()
        {
            for (uint a = 0; a < TextBoxes.Count(); a++)
                delete TextBoxes(a);

            if (Image)          { delete Image; }
            if (PipelineSVG)    { delete PipelineSVG; }
            if (SceneSVG)       { delete SceneSVG; }
        }

    protected:
        Path2D              DrawingPath;
        Texture2D*          Image;
        bool                IsEnteringText;
        ShaderPipeline*     PipelineSVG;
        Vector2             LastClickPosition;
        Quad3D              Quad;
        Scene3D*            SceneSVG;
        List<Text2D*>       TextBoxes;



        void CreateSceneResources() override
        {
            AdvancedRenderer::CreateSceneResources();
            SceneSVG = new Scene3D();
            Image = new Texture2D("../ImageDisplay/House (11250x8627).jpg");
            Image->Bind();

            Quad
                .Position(RenderWindow->ClientArea().Scale() / 2.0f)
                .Scale(Vector3(RenderWindow->ClientArea().Scale(), 0.0f));

            DrawingPath
                .JoinStyle(JoinStyles::Round)
                .StrokeColor(Color4(1.0f, 0.0f, 0.0f, 0.875f))
                .StrokeWidth(2)

                .Color(Color4(0.0f, 0.0f, 1.0f, 0.75f));

            RenderScene->Add(Quad);
            SceneSVG->Add(DrawingPath);
        }
        void CreateShaderPipeline() override
        {
            RenderPipeline = new ShaderPipeline("../Renderers/Shaders/Default.vsl", "../ImageDisplay/TexturedShading.psl");
            Renderer->Pipeline(RenderPipeline);

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

                if (DrawingPath.IsEmpty() || DrawingPath.IsClosed())
                    newPt.Command = PathCommands::Move;

                DrawingPath.Add(newPt);
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
                DrawingPath.Add
                ({ 
                    PathCommands::SmoothQuadraticCurve, 
                    { 
                        PointerPosition.X, 
                        RenderWindow->ClientArea().Height - PointerPosition.Y,
                    }
                });

            else if (evt.Key == KeyboardKeys::E)
                DrawingPath.Add({ PathCommands::Close, { } });
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
                    SceneSVG->Remove(*TextBoxes(a));
                    delete TextBoxes(a);
                }

                TextBoxes.Clear();
                DrawingPath.Clear();

            }

            AdvancedRenderer::ProcessKeyPress(evt);
        }



        void UpdateScene() override
        {
            const Matrix4x4& projection = Projection.ToMatrix4x4();
            const Matrix4x4& view = View.ToMatrix4x4();

            nvMatrixLoadIdentity(TransformMatrices::Projection);
            nvMatrixLoadf(TransformMatrices::Projection, (projection * view).ToArray());

            Renderer->Pipeline(RenderPipeline);
            Renderer->Scene(RenderScene);

            Renderer->Update();
            Renderer->Execute();

            Renderer->Pipeline(PipelineSVG);
            Renderer->Scene(SceneSVG);

            AdvancedRenderer::UpdateScene();
        }
        

    private:

        void CreateTextBox()
        {
            Text2D* text = new Text2D();
            text->
                Color(Color4::Yellow)
                .Scale(0.0125f, 0.0125f)
                .Position(PointerPosition.X, RenderWindow->ClientArea().Height - PointerPosition.Y);

            TextBoxes.Append(text);
            SceneSVG->Add(*text);
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}