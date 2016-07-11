/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#pragma once
#include "Area.h"
#include "PlatformAPI.h"
#include "TypeDefinitions.h"
#include "Vector2.h"



namespace Cyclone
{
    namespace Platform
    {
        using namespace Cyclone::Utilities;
        


        class Window3D
        {
            public:

                PlatformAPI Window3D(const Area& displayArea, const string& title);
                PlatformAPI ~Window3D();


            private:
                struct _window3D;

                _window3D*      _internal;
                //HWND            _id;
                //Area            _displayArea;
                //string          _title;

        };
    }
}