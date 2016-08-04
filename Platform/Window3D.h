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
        /// <summary> A class that represents a native operating system window and whose client area can be used for 3D rendering. </summary>
        class Window3D
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the pixel size and position of this window (including borders) on the display. </summary>
                const Area& DisplayArea()   const { return _displayArea; }
                /// <summary> Gets the height of this window (including borders) in pixels. </summary>
                uint Height()               const { return (uint)_displayArea.Height; }
                /// <summary> Gets whether this window has any borders or decorations surrounding it. </summary>
                bool IsBordered()           const { return _isBordered; }
                /// <summary> Gets the pixel size and position of this window (excluding borders) on the display. </summary>
                const Area& RenderArea()    const { return _renderArea; }
                /// <summary> Gets the size of this window (including borders) in pixels. </summary>
                Vector2 Size()              const { return _displayArea.Scale(); }
                /// <summary> Gets the width of this window (including borders) in pixels. </summary>
                uint Width()                const { return (uint)_displayArea.Width; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs a new 3D rendering window occupying a specified area of the computer display. </summary>
                /// <param name="displayArea"> The desired pixel position and size of the window on the desktop. </param>
                /// <param name="title"> The desired title of the window to be displayed on the border. </param>
                PlatformAPI Window3D(const Area& displayArea, const string& title);
                PlatformAPI ~Window3D();



                /** PUBLIC UTILITIES **/
                /// <summary> Pulls the next event from the window's event queue and processes it. </summary>
                /// <returns> A Boolean <c>true</c> if event processing can continue, or <c>false</c> otherwise. </returns>
                /// <remarks>
                ///     This method essentially performs a single iteration of an event loop (or, as it's referred to on the Windows 
                ///     platform, a 'message pump'). 
                /// </remarks>
                PlatformAPI bool ProcessEvent();



                /** INTERNAL UTILITIES **/
                /// <summary> Gets the device context associated with this window on the Windows platform only. </summary>
                /// <returns>
                ///     A pointer-to-void that may be freely cast to a Windows-specific device context.
                ///     <para> </para>
                ///     When executing this method on the Windows platform, this method returns a <see cref="HDC"/> 
                ///     instance. On Linux, however, this method will always return a <c>nullptr</c>.
                /// </returns>
                /// <remarks>
                ///     On Windows (and, by extension, DirectX), there are two separate contexts to keep track of. 
                ///     One is the device context, which represents a configuration structure that details a specific 
                ///     surface or output on which rendering occurs. For example, this structure may dictate whether 
                ///     drawing occurs through GDI or through a device driver such as the GPU. The second context is 
                ///     called the rendering context and is discussed in more detail within the <see cref="GetRenderContext"/>
                ///     method.
                /// 
                ///     Linux also utilitizes device contexts. However, unlike on Windows, direct interaction with 
                ///     them is not required to set up a rendering context, and therefore they are not discussed 
                ///     here. This is why execution of this method from a Linux platform will always return a <c>nullptr</c>.
                /// </remarks>
                InternalAPI void* GetDeviceContext()    const;
                /// <summary> Gets the rendering context associated with this window. </summary>
                /// <returns>
                ///     A pointer-to-void that may be freely cast to a platform-specific rendering context.
                ///     <para> </para>
                ///     When executing this method on the Windows platform, the return value may be cast to a <see cref="HGLRC"/>
                ///     instance. On Linux, this value may be cast to a <see cref="GLXContext"/>.
                /// </returns>
                /// <remarks>
                ///     When rendering on the Windows platform, there are two separate contexts to keep track of. One is 
                ///     the device context, discussed in the remarks section of <see cref="GetDeviceContext"/>. The other 
                ///     is called the rendering context, and it represents a configuration structure that details specific 
                ///     drawing parameters for rendering on a device context. For example, this structure may dictate the 
                ///     number of color channels available for rendering, how many bits of memory are required per color 
                ///     channel, and the configuration of the system-level framebuffer used to present images on-screen to 
                ///     the user.
                /// 
                ///     Linux also utilizes rendering contexts in more or less the same way. However, the format of its 
                ///     contexts are different and incompatible with those used on Windows. 
                /// </remarks>
                InternalAPI void* GetRenderContext()    const;
                /// <summary> Gets the system-level handle used to address this particular window. </summary>
                /// <returns>
                ///     A pointer-to-void that may be freely cast to a platform-specific window handle.
                /// </returns>
                /// <remarks>
                /// 
                /// </remarks>
                InternalAPI void* GetWindowHandle()     const;



                /** RENDERING UTILITIES **/
                /// <summary> Makes this window the primary rendering surface for the program. </summary>
                /// <remarks>
                ///     This method loads the rendering context associated with it for immediate use. This in turn directs 
                ///     all subsequent rendering operations (executed on the same thread) to output their results into this 
                ///     window.
                /// </remarks>
                InternalAPI void Bind()                 const;
                /// <summary> Swaps the front and back rendering buffers, displaying the contents of the backbuffer to the user. </summary>
                /// <remarks>
                ///     On Windows, and in particular within DirectX, the rendering buffer associated with a window is often 
                ///     called a 'swap-chain'. The same construct exists OpenGL and in Linux, although the term 'swap-chain' is 
                ///     far less common in those domains. It represents two separate framebuffers on which rendering occurs that 
                ///     are constantly being cycled or swapped with one another in order to present drawings on-screen to the 
                ///     user. One of these framebuffers is called a 'front' buffer, while the other is called the 'back' buffer.
                /// 
                ///     The front-buffer contains image data from a previous iteration of the rendering loop. In other words, 
                ///     it holds rendering outputs that are currently on the computer monitor being displayed for the user. 
                ///     Typically, whichever framebuffer is currently the front-buffer is immutable. The back-buffer, however, 
                ///     is modifiable and is usually where any new rendering occurs. Thus, as a program proceeds through its 
                ///     rendering loop and a shader pipeline produces new outputs, the back-buffer is where they are stored. 
                ///     On completion of a rendering loop iteration, the front- and back-buffers swap positions, and what was 
                ///     originally the front-buffer now becomes the back-buffer and vice versa. Its contents are also usually 
                ///     cleared at this point, providing a fresh blank surface on which the next iteration can draw.
                /// 
                ///     Such a scheme is usually referred to as 'double-buffering' and is the typical mode of operation for 
                ///     rendering on most popular platforms. Other schemes, such as triple-buffering, are also sometimes used, 
                ///     but are not discussed here.
                /// </remarks>
                InternalAPI void Present()              const;
                /// <summary> Makes the loading window the primary rendering surface for the program. </summary>
                /// <remarks>
                ///     This method makes the <see cref="LoadingWindow"/> the current rendering surface. Because the loading 
                ///     window is completely invisible to the end-user by default, invoking this method without binding 
                ///     another rendering window means that any further drawing outputs will be lost and not shown on-screen.
                /// </remarks>
                InternalAPI void Unbind()               const;

            private:
                struct          _window3D;
                _window3D*      Internals;



                /** PROPERTY DATA **/
                Area            _displayArea;
                bool            _isBordered;
                Area            _renderArea;
                string          _title;

        };
    }
}