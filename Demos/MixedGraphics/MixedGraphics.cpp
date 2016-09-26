
#include "AdvancedRenderer.h"
#include "Console.h"
#include "EnumerationsSVG.h"
#include "GPU.h"
#include "NVPR.h"
#include "Utilities.h"
#include "Window3D.h"

#include "Buffers/FrameBuffer.h"
#include "Collections/Vector.h"
#include "Geometry/Geometry3D.h"
#include "Geometry/Mesh3D.h"
#include "Geometry/Scene3D.h"
#include "Geometry/Path2D.h"

#include "Imaging/Color4.h"
#include "Math/Constants.h"
#include "Pipelines/ShaderPipeline.h"

using namespace Cyclone::Platform;
using namespace Cyclone::SVG;
using namespace Cyclone::OpenGL;
using namespace Cyclone::Utilities;
using namespace Renderers;

const static string SVG = "m 120.63853,919.55219 9.13207,0 0,15.24165 -9.13207,0 z m -11.65033,0 9.13207,0 0,15.24165 -9.13207,0 z m 35.3562,16.18832 -11.44143,11.72414 -16.14684,-0.0348 -11.39365,-11.7733 0.0338,-16.6152 11.44142,-11.72415 16.14684,0.0348 11.39366,11.7733 z m 89.58171,66.00899 0,-6.20473 m -33.97348,40.33093 -4.52978,0 m -12.07946,-58.1696 -17.36422,-17.83867 4.5298,-4.65357 -7.44495,-7.91467 2.41112,-2.45336 -0.0143,-5.15198 11.08793,0.008 0,-3.87805 9.05959,0 0,3.87805 3.77483,0 0,9.30713 3.77483,0 0,24.04342 -2.26489,0 0,8.56669 -0.84322,-0.0223 -5.19651,-5.44209 -1.50993,1.55118 0,3e-5 -1.4e-4,-3e-5 3e-5,0 0,3e-5 z m -17.88252,-38.01225 0,-16.14101 m 20.14752,16.14916 -7e-5,-15.51176 m -9.67757,61.84043 1.614,-1.57148 -17.89765,-16.8445 -4.44023,4.40106 -8.18704,-8.10516 -3.11493,3.23522 -4.42637,-0.009 -0.20244,10.67469 -3.37195,0.0688 -0.0225,9.25943 2.99666,0.003 -0.0458,2.9665 10.36822,0.28379 -0.0231,3.71713 23.5586,-0.0677 0.0705,-2.31207 6.53913,0.13129 1.20164,-1.19725 -4.61668,-4.63397 -4e-5,-6e-5 -1e-5,-3e-5 0,-10e-6 1e-5,0 z m -36.45222,-18.89363 -22.73283,0 m 27.1592,0.009 21.57024,-22.29998 m -48.36449,42.21732 21.76765,0.0799 m 56.54455,48.73265 0,-10.0828 -1.50994,0 0,-7.6584 -4.66226,-0.038 -10.36507,-10.8092 -0.006,-2.4356 -5.35059,0 0,-2.3268 -23.40394,0 0,3.878 -11.32449,0 0,3.1024 -2.26491,0 0,5.4291 20.38408,10e-5 0,36.4529 27.17877,0 0,-15.5119 11.32449,0 0,0 2e-5,0 -2e-5,0 0,0 -4e-5,0 z m -78.38999,-26.4501 21.76766,0.08 m 0,-10e-5 0.0778,-22.36244 m 78.43854,42.52784 -8.30463,-7.7559 -2.26489,0 -3.17389,-3.6801 -2.09194,-0.016 -0.0189,7.5741 -1.50993,0 0,10.0827 10.56952,0 0,15.5119 7.54966,0 5.00384,-4.8914 -5.7588,-6.7425 0,-10.0828 1e-5,0 0,0 z m 0.75495,21.7167 -104.36909,0 m 120.22339,-67.47675 0,11.63392 -10.56952,0 0,-3.26767 -8.82506,0.0162 -1.68802,-1.7681 4.90281,-5.20928 -8.47204,-8.65663 -5.02861,4.83644 -2.0563,-2.28842 0.0282,-6.15479 -2.2649,-5e-5 0,-24.04343 4.52979,0 0,-9.30713 2.2649,0 0,-3.87797 6.03973,0 0,20.94105 36.23838,0 0,27.05066 -15.09933,0.0951 0,2e-5 0,3e-5 1e-5,0 z m -21.13906,-48.0869 0,-11.76318 m -6.03973,15.64115 -7e-5,-15.51176 m -2.26483,15.51176 -15.0992,8e-5 m 30.19854,72.9058 0,-2.3267 -4.95807,-3.1435 0.0213,-2.3497 8.60831,-0.034 0.1033,-3.0042 10.56952,0 0,10.8583 15.09932,0 0,8.5315 -5.42185,5.298 -6.65143,-6.846 -11.33066,0 -6.03973,-6.9803 0,0 z m 29.44367,-85.84899 0,94.38049 m 0,0 -30.95362,30.2483 m -39.1829,-44.1009 0.14751,-15.09062 10.56976,-10.56496 14.80039,0.1495 10.36116,10.77638 -0.1475,15.0906 -10.56976,10.565 -14.8004,-0.1495 z m 55.0372,-154.31182 0,6.20471 m -33.97348,-40.33093 -4.52978,3e-5 m -12.07946,58.16957 -17.36422,17.83867 4.5298,4.65357 -7.44495,7.91467 2.41112,2.45336 -0.0143,5.15198 11.08793,-0.008 0,3.87805 9.05959,0 0,-3.87805 3.77483,0 0,-9.30713 3.77483,0 0,-24.04342 -2.26489,0 0,-8.56669 -0.84322,0.0223 -5.19651,5.44209 -1.50993,-1.55118 0,-3e-5 -1.4e-4,3e-5 3e-5,0 0,-3e-5 z m -17.88252,38.01225 0,16.14101 m 20.14752,-16.14916 -7e-5,15.51176 m -9.67757,-61.84043 1.614,1.57148 -17.89765,16.8445 -4.44023,-4.40106 -8.18704,8.10516 -3.11493,-3.23522 -4.42637,0.009 -0.20244,-10.67469 -3.37195,-0.0688 -0.0225,-9.25943 2.99666,-0.003 -0.0458,-2.9665 10.36822,-0.28379 -0.0231,-3.71713 23.5586,0.0677 0.0705,2.31207 6.53913,-0.13129 1.20164,1.19725 -4.61668,4.63397 -4e-5,6e-5 -1e-5,3e-5 0,1e-5 1e-5,0 z m -36.45222,18.89363 -22.73283,0 m 27.1592,-0.009 21.57024,22.29998 m -48.36449,-42.21732 21.76765,-0.0799 m 56.54455,-48.73262 0,10.08273 -1.50994,0 0,7.65842 -4.66226,0.0379 -10.36507,10.80921 -0.006,2.43554 -5.35059,0 0,2.32678 -23.40394,0 0,-3.87797 -11.32449,0 0,-3.10238 -2.26491,0 0,-5.42916 20.38408,-10e-6 0,-36.45293 27.17877,0 0,15.51189 11.32449,0 0,10e-6 2e-5,0 -2e-5,0 0,2e-5 -4e-5,0 z m -78.38999,26.45009 21.76766,-0.0799 m 0,-10e-6 0.0778,22.36243 m 78.43854,-42.52786 -8.30463,7.75595 -2.26489,0 -3.17389,3.68008 -2.09194,0.016 -0.0189,-7.57407 -1.50993,0 0,-10.08272 10.56952,0 0,-15.51189 7.54966,0 5.00384,4.89143 -5.7588,6.74249 0,10.08272 1e-5,0 0,3e-5 z m 0.75495,-21.71667 -104.36909,0 m 120.22339,67.47674 0,-11.63392 -10.56952,0 0,3.26767 -8.82506,-0.0162 -1.68802,1.7681 4.90281,5.20928 -8.47204,8.65663 -5.02861,-4.83644 -2.0563,2.28842 0.0282,6.15479 -2.2649,5e-5 0,24.04343 4.52979,0 0,9.30713 2.2649,0 0,3.87797 6.03973,0 0,-20.94105 36.23838,0 0,-27.05066 -15.09933,-0.0951 0,-2e-5 0,-3e-5 1e-5,0 z m -21.13906,48.0869 0,11.76318 m -6.03973,-15.64115 -7e-5,15.51176 m -2.26483,-15.51176 -15.0992,-8e-5 m 30.19854,-72.90584 0,2.32678 -4.95807,3.14349 0.0213,2.34963 8.60831,0.0343 0.1033,3.00418 10.56952,0 0,-10.85832 15.09932,0 0,-8.53154 -5.42185,-5.29795 -6.65143,6.84597 -11.33066,0.003 -6.03973,6.98035 0,-4e-5 z m 29.44367,85.84903 0,-94.38053 m 0,0 -30.95362,-30.24825 m -39.1829,44.1009 0.14751,15.0906 10.56976,10.56496 14.80039,-0.1495 10.36116,-10.77638 -0.1475,-15.09061 -10.56976,-10.56496 -14.8004,0.14951 z m -162.815012,154.31183 0,-6.20473 m 33.973484,40.33093 4.529781,0 m 12.079456,-58.1696 17.364218,-17.83867 -4.529796,-4.65357 7.444953,-7.91467 -2.411119,-2.45336 0.01427,-5.15198 -11.087936,0.008 0,-3.87805 -9.059592,0 0,3.87805 -3.77483,0 0,9.30713 -3.77483,0 0,24.04342 2.264898,0 0,8.56669 0.843222,-0.0223 5.196506,-5.44209 1.509932,1.55118 0,3e-5 1.36e-4,-3e-5 -3e-5,0 0,3e-5 z m 17.882524,-38.01225 0,-16.14101 m -20.147528,16.14916 7.6e-5,-15.51176 m 9.677569,61.84043 -1.614004,-1.57148 17.897654,-16.8445 4.440234,4.40106 8.187036,-8.10516 3.11493,3.23522 4.42637,-0.009 0.20244,10.67469 3.37195,0.0688 0.0225,9.25943 -2.99666,0.003 0.0458,2.9665 -10.36822,0.28379 0.0231,3.71713 -23.558597,-0.0677 -0.07051,-2.31207 -6.53913,0.13129 -1.201634,-1.19725 4.616677,-4.63397 3.8e-5,-6e-5 8e-6,-3e-5 0,-10e-6 -8e-6,0 z m 36.45222,-18.89363 22.73283,0 m -27.1592,0.009 -21.570235,-22.29998 m 48.364485,42.21732 -21.76765,0.0799 m -56.544547,48.73265 0,-10.0828 1.509932,0 0,-7.6584 4.66227,-0.038 10.365064,-10.8092 0.006,-2.4356 5.350587,0 0,-2.3268 23.403946,0 0,3.878 11.324488,0 0,3.1024 2.26491,0 0,5.4291 -20.384077,10e-5 0,36.4529 -27.178776,0 0,-15.5119 -11.32449,0 0,0 -1.5e-5,0 1.5e-5,0 0,0 3.8e-5,0 z m 78.389987,-26.4501 -21.76766,0.08 m 0,-10e-5 -0.0778,-22.36244 m -78.438541,42.52784 8.304626,-7.7559 2.264898,0 3.173885,-3.6801 2.091943,-0.016 0.01895,7.5741 1.509932,0 0,10.0827 -10.569524,0 0,15.5119 -7.54966,0 -5.003839,-4.8914 5.758805,-6.7425 0,-10.0828 -1.5e-5,0 0,0 z m -0.754951,21.7167 104.369092,0 m -120.223392,-67.47675 0,11.63392 10.569523,0 0,-3.26767 8.825062,0.0162 1.688021,-1.7681 -4.902809,-5.20928 8.472039,-8.65663 5.028602,4.83644 2.056308,-2.28842 -0.02816,-6.15479 2.264898,-5e-5 0,-24.04343 -4.529796,0 0,-9.30713 -2.264898,0 0,-3.87797 -6.039728,0 0,20.94105 -36.23838222,0 0,27.05066 15.09933522,0.0951 0,2e-5 0,3e-5 -1.5e-5,0 z m 21.139062,-48.0869 0,-11.76318 m 6.039728,15.64115 7.6e-5,-15.51176 m 2.264822,15.51176 15.099199,8e-5 m -30.198534,72.9058 0,-2.3267 4.958066,-3.1435 -0.02129,-2.3497 -8.608304,-0.034 -0.103302,-3.0042 -10.569523,0 0,10.8583 -15.09932022,0 0,8.5315 5.42184862,5.298 6.6514316,-6.846 11.330665,0 6.039728,-6.9803 0,0 z m -29.44367322,-85.84899 0,94.38049 m 0,0 30.95362022,30.2483 M 71.1111,1007.2867 70.963592,992.19608 60.39383,981.63112 45.593439,981.78062 35.23228,992.557 l 0.147501,15.0906 10.569762,10.565 14.800398,-0.1495 z m -55.037202,-154.31182 0,6.20471 m 33.973484,-40.33093 4.529781,3e-5 m 12.079456,58.16957 17.364218,17.83867 -4.529796,4.65357 7.444953,7.91467 -2.411119,2.45336 0.01427,5.15198 -11.087936,-0.008 0,3.87805 -9.059592,0 0,-3.87805 -3.77483,0 0,-9.30713 -3.77483,0 0,-24.04342 2.264898,0 0,-8.56669 0.843222,0.0223 5.196506,5.44209 1.509932,-1.55118 0,-3e-5 1.36e-4,3e-5 -3e-5,0 0,-3e-5 z m 17.882524,38.01225 0,16.14101 m -20.147528,-16.14916 7.6e-5,15.51176 m 9.677569,-61.84043 -1.614004,1.57148 17.897654,16.8445 4.440234,-4.40106 8.187036,8.10516 3.11493,-3.23522 4.42637,0.009 0.20244,-10.67469 3.37195,-0.0688 0.0225,-9.25943 -2.99666,-0.003 0.0458,-2.9665 -10.36822,-0.28379 0.0231,-3.71713 -23.558597,0.0677 -0.07051,2.31207 -6.53913,-0.13129 -1.201634,1.19725 4.616677,4.63397 3.8e-5,6e-5 8e-6,3e-5 0,1e-5 -8e-6,0 z m 36.45222,18.89363 22.73283,0 m -27.1592,-0.009 -21.570235,22.29998 m 48.364485,-42.21732 -21.76765,-0.0799 m -56.544547,-48.73262 0,10.08273 1.509932,0 0,7.65842 4.66227,0.0379 10.365064,10.80921 0.006,2.43554 5.350587,0 0,2.32678 23.403946,0 0,-3.87797 11.324488,0 0,-3.10238 2.26491,0 0,-5.42916 -20.384077,-10e-6 0,-36.45293 -27.178776,0 0,15.51189 -11.32449,0 0,10e-6 -1.5e-5,0 1.5e-5,0 0,2e-5 3.8e-5,0 z m 78.389987,26.45009 -21.76766,-0.0799 m 0,-10e-6 -0.0778,22.36243 m -78.438541,-42.52786 8.304626,7.75595 2.264898,0 3.173885,3.68008 2.091943,0.016 0.01895,-7.57407 1.509932,0 0,-10.08272 -10.569524,0 0,-15.51189 -7.54966,0 -5.003839,4.89143 5.758805,6.74249 0,10.08272 -1.5e-5,0 0,3e-5 z m -0.754951,-21.71667 104.369092,0 m -120.223392,67.47674 0,-11.63392 10.569523,0 0,3.26767 8.825062,-0.0162 1.688021,1.7681 -4.902809,5.20928 8.472039,8.65663 5.028602,-4.83644 2.056308,2.28842 -0.02816,6.15479 2.264898,5e-5 0,24.04343 -4.529796,0 0,9.30713 -2.264898,0 0,3.87797 -6.039728,0 0,-20.94105 -36.23838222,0 0,-27.05066 15.09933522,-0.0951 0,-2e-5 0,-3e-5 -1.5e-5,0 z m 21.139062,48.0869 0,11.76318 m 6.039728,-15.64115 7.6e-5,15.51176 m 2.264822,-15.51176 15.099199,-8e-5 m -30.198534,-72.90584 0,2.32678 4.958066,3.14349 -0.02129,2.34963 -8.608304,0.0343 -0.103302,3.00418 -10.569523,0 0,-10.85832 -15.09932022,0 0,-8.53154 5.42184862,-5.29795 6.6514316,6.84597 11.330665,0.003 6.039728,6.98035 0,-4e-5 z m -29.44367322,85.84903 0,-94.38053 m 0,0 30.95362022,-30.24825 m 39.182902,44.1009 -0.147508,15.0906 -10.569762,10.56496 -14.800391,-0.1495 -10.361159,-10.77638 0.147501,-15.09061 10.569762,-10.56496 14.800398,0.14951 z";

class Program : public AdvancedRenderer
{
    public:

        Program() :
            AdvancedRenderer("NVIDIA Basic Rounded Rectangle Rendering"),
            PipelineSVG(nullptr),
            SceneSVG(nullptr),
            Sphere(Geometry3D::Sphere(4))
        {
            Initialize();
            nvPathStencilDepthOffset(-0.05f, -1);
            nvPathCoverDepthFunc(GL_ALWAYS);

            Console::WriteLine(num2str(Sphere.Points().Count()) + " vertices being drawn!");
        }
        ~Program()
        {
            if (SceneSVG)       { delete SceneSVG; }
            if (PipelineSVG)    { delete PipelineSVG; }
        }

    protected:

        const float     MoveSpeed = 16.0f;
        Path2D          Path;
        ShaderPipeline* PipelineSVG;
        Mesh3D          Sphere;
        Scene3D*        SceneSVG;
        Vector3         WalkingDirection;


        void CreateSceneResources() override
        {
            AdvancedRenderer::CreateSceneResources();
            SceneSVG = new Scene3D();

            Sphere.Scale(100, 100, 100)
                .Color(Color4(0.0f, 0.75f, 1.0f))
                .Position(Vector3(RenderWindow->ClientArea().Center(), 50))
                .Pitch(90)
                .Roll(90);

            Path
                .Path(SVG)
                .JoinStyle(JoinStyles::Round)
                .StrokeColor(Color4::Cyan)
                .StrokeWidth(2)

                .Color(Color4::Red)
                .Scale(1)
                .Position(Vector3(RenderWindow->ClientArea().Scale() * Vector2(0.375f, -0.5f), 0.0f));

            RenderScene->Add(Sphere);
            SceneSVG->Add(Path);
        }
        void CreateShaderPipeline() override
        {
            AdvancedRenderer::CreateShaderPipeline();
            PipelineSVG = new ShaderPipeline("../Renderers/Shaders/SVG.psl");
        }
        void UpdateScene() override
        {
            Vector3 dir = WalkingDirection;
            if (dir != Vector3::Zero)
            {
                View.Translate(dir.Normalize() * MoveSpeed);
                Renderer->View(View);
            }

            const Matrix4x4& projection = Renderer->Projection().ToMatrix4x4();
            const Matrix4x4& view = Renderer->View().ToMatrix4x4();

            nvMatrixLoadIdentity(TransformMatrices::Projection);
            nvMatrixLoadf(TransformMatrices::Projection, (projection * view).ToArray());

            static float count = 0.0f;
            Path.Z(-250 * sin(count));
            count += 0.02f;

            Color4 color
            (
                0.5f * sinf(Sphere.Pitch()) + 0.5f,
                0.25f * cosf(Sphere.Yaw()) + 0.75f,
                0.125f * sinf(Sphere.Roll()) + 0.875
            );

            Sphere.Color(color).Rotate(0.01f);
            RenderScene->Update(Sphere);

            Renderer->RenderPipeline(PipelineSVG);
            Renderer->Scene(SceneSVG);

            Renderer->Update();
            Renderer->Execute();

            Renderer->RenderPipeline(RenderPipeline);
            Renderer->Scene(RenderScene);

            AdvancedRenderer::UpdateScene();
        }

};



int main(int nargs, char** args)
{
    Program app;
    app.Execute();
    return 0;
}
