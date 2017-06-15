/* CHANGELOG
 * Written by Josh Grooms on 20170614
 */

#pragma once
#include "AdvancedRenderer.h"

#include "Geometry/Entity3D.h"
#include "Geometry/Mesh3D.h"
#include "Math/Constants.h"
#include "Pipelines/ShaderPipeline.h"
#include "Scenes/Scene3D.h"
#include "include/cef_app.h"

using namespace Cyclone::OpenGL;
using namespace Cyclone::Renderers;



class Program: public AdvancedRenderer
{
    public:

        //Camera& ViewMatrix()                { return View; }
        //Entity3D& Browser()                 { return BrowserPage; }
        Texture3D* Image()                  { return BrowserImage; }
        //const Vector2& PointerPosition()    { return _pointerPosition; }
        const Vector2& CursorPosition()     { return _cursorPosition; }
        Window3D* Window()                  { return RenderWindow; }

        Program();
            
        ~Program()                          { if (BrowserImage) { delete BrowserImage; } }


        void Execute() override;
        void UpdateBrowser()                { RenderScene->Update(BrowserPage); }

    protected:

        Entity3D        Cube;
        Entity3D        BrowserPage;
        Texture3D*      BrowserImage;
        Vector2         _cursorPosition;

        void CreateSceneResources()                                 override;

        void UpdateScene()                                          override;

        void ProcessButtonPress(const PointerClickEvent& evt);

        void ProcessButtonRelease(const PointerClickEvent& evt);

        void ProcessPointerMotion(const PointerMotionEvent& evt)    override;
};
