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

        Resource<Texture3D> Image()         { return _image; }
        bool IsNavigationEnabled()          { return _isNavigationEnabled; }
        const Vector2& CursorPosition()     { return _cursorPosition; }
        Window3D* Window()                  { return RenderWindow; }

        Program();

        //~Program()                          { if (_image) { delete BrowserImage; } }


        void Execute() override;
        void UpdateBrowser()                { RenderScene->Update(*_browser); }

    protected:

        Resource<Entity3D>  Cube;

        Resource<Entity3D>  _browser;
        Resource<Texture3D> _image;
        bool                _isNavigationEnabled;
        Vector2             _cursorPosition;

        void CreateSceneResources()                                 override;

        void UpdateScene()                                          override;

        void ProcessButtonPress(const PointerClickEvent& evt);

        void ProcessButtonRelease(const PointerClickEvent& evt);

        void ProcessKeyPress(const KeyboardEvent& evt)              override;

        void ProcessKeyRelease(const KeyboardEvent& evt)            override;

        void ProcessPointerMotion(const PointerMotionEvent& evt)    override;
};
