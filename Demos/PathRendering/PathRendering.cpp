/* CHANGELOG 
 * Written by Josh Grooms on 20160915
 */

#include "BasicRenderer.h"
#include "GPU.h"
#include "NVPR.h"
#include "Window3D.h"

using namespace Cyclone::Platform;
using namespace Cyclone::Utilities;
using namespace Renderers;


#define GL_PATH_STROKE_WIDTH_NV                             0x9075
#define GL_PATH_JOIN_STYLE_NV                               0x9079
#define GL_ROUND_NV                                         0x90A4
#define GL_PATH_FORMAT_SVG_NV                               0x9070
#define GL_PATH_FORMAT_PS_NV                                0x9071
#define GL_CLOSE_PATH_NV                                    0x00
#define GL_MOVE_TO_NV                                       0x02
#define GL_LINE_TO_NV                                       0x04
#define GL_COUNT_UP_NV                                      0x9088
#define GL_CONVEX_HULL_NV                                   0x908B
#define GL_BOUNDING_BOX_NV                                  0x908D



class Program : public BasicRenderer
{
    public:

        Program() : BasicRenderer("NVIDIA Path Rendering")
        {
            ClearColor = Color4::Black;

            Initialize();
        }

        void Execute() override
        {
            while (CanContinue())
            {
                RenderWindow->ProcessEvent();
                Renderer->Clear(ClearColor);

                glClearStencil(0);
                glStencilMask(~0);
                glClear(GL_STENCIL_BUFFER_BIT);

                Renderer->Execute();
                Renderer->Present();
            }
        }

    protected:

        void CreateSceneResources() override
        {
            string svgString = "M100,180 L40,10 L190,120 L10,120 L160,10 z";
            nvPathString(42, GL_PATH_FORMAT_SVG_NV, svgString.size(), svgString.c_str());

            nvPathParameteri(42, GL_PATH_JOIN_STYLE_NV, GL_ROUND_NV);
            nvPathParameterf(42, GL_PATH_STROKE_WIDTH_NV, 6.5f);
        }

        
};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}