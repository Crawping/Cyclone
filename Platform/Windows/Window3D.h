/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#pragma once
#include "Area.h"
#include "Window3D.h"
#include "TypeDefinitions.h"
#include "Vector2.h"

namespace 
{
    struct  HDC_;
    struct  HWND_;
    struct  Vector2;

    typedef int* HWND;
    typedef int* HDC;
}


namespace Cyclone::Platform
{
    using namespace Cyclone::Utilities;


    class Window3D
    {
        public:

            Window3D(const Area& displayArea, const string& title);
            ~Window3D();


        private:
            Area        _displayArea;
            HWND        _id;
            string      _title;

            HDC         DeviceContext;

    };
}