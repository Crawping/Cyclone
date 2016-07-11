/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#pragma once
#include "Area.h"
#include "PlatformAPI.h"
#include "TypeDefinitions.h"



namespace Cyclone
{
    namespace Platform
    {
        using namespace Cyclone::Utilities;
        


        class Window3D
        {
            public:
                const Area& DisplayArea()   const { return _displayArea; }
                bool IsBordered()           const { return _isBordered; }

                PlatformAPI Window3D(const Area& displayArea, const string& title);
                PlatformAPI ~Window3D();


            private:
                struct          _window3D;
                _window3D*      Internals;

                Area            _displayArea;
                bool            _isBordered;
                string          _title;

        };
    }
}