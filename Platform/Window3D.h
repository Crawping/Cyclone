/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#pragma once
#include "Area.h"
#include "PlatformAPI.h"
#include "TypeDefinitions.h"



namespace Cyclone
{
    using namespace Utilities;

    namespace Platform
    {
        class Window3D
        {
            public:

                /** PROPERTIES **/
                const Area& DisplayArea()   const { return _displayArea; }
                uint Height()               const { return (uint)_displayArea.Height; }
                bool IsBordered()           const { return _isBordered; }
                Vector2 Size()              const { return _displayArea.Scale(); }
                uint Width()                const { return (uint)_displayArea.Width; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                PlatformAPI Window3D(const Area& displayArea, const string& title);
                PlatformAPI ~Window3D();



                PlatformAPI bool ProcessEvents();


                InternalAPI void* GetDeviceContext()    const;
                InternalAPI void* GetRenderContext()    const;
                InternalAPI void* GetWindowHandle()     const;


                InternalAPI void Bind()                 const;

                InternalAPI void Present()              const;

                InternalAPI void Unbind()               const;


            private:
                struct          _window3D;
                _window3D*      Internals;



                /** PROPERTY DATA **/
                Area            _displayArea;
                bool            _isBordered;
                string          _title;

        };
    }
}