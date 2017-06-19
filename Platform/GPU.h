/* CHANGELOG
 * Written by Josh Grooms on 20160707
 */

#pragma once
#include "GraphicsSettings.h"
#include "PlatformAPI.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/UniformData.h"
#include "Collections/List.h"
#include "Imaging/Color4.h"
#include "Interfaces/IReportable.h"
#include "Interfaces/IScene.h"
#include "Pipelines/GraphicsPipeline.h"



namespace Cyclone
{

    /** FORWARD DECLARATIONS **/
    namespace { using namespace OpenGL; }
    namespace OpenGL
    {
        class FrameBuffer;
        class Scene3D;
    }
    namespace Utilities { class ISpatialTransform; }



    namespace Platform
    {
        class Window3D;



        class GPU : public IReportable
        {
            public:

                /** PROPERTIES **/
                CullingModes CullingMode()                  const { return _settings.CullingMode; }

                bool IsBlendEnabled()                       const { return _settings.IsBlendEnabled; }

                bool IsDepthTestEnabled()                   const { return _settings.IsDepthTestEnabled; }

                bool IsStencilTestEnabled()                 const { return _settings.IsStencilTestEnabled; }

                /// <summary> Gets a pointer to the projection transformation being used by the rendering pipeline. </summary>
                const ISpatialTransform* Projection()       const { return _settings.Projection; }
                /// <summary> Gets a pointer to the shader pipeline currently being used to render images. </summary>
                const IGraphicsPipeline* Pipeline()         const { return _settings.Pipeline; }

                const GraphicsSettings& Settings()          const { return _settings; }
                /// <summary> Gets a pointer to the framebuffer to which all rendering currently occurs. </summary>
                const FrameBuffer* Target()                 const { return _settings.Target; }
                /// <summary> Gets a pointer to the view transformation being used by the rendering pipeline. </summary>
                const ISpatialTransform* View()             const { return _settings.View; }
                /// <summary> Gets a pointer to the window currently being used to display the render target. </summary>
                const Window3D* Window()                    const { return _renderWindow; }



                PlatformAPI GPU& CullingMode(CullingModes value);
                PlatformAPI GPU& IsBlendEnabled(bool value);
                PlatformAPI GPU& IsDepthTestEnabled(bool value);
                PlatformAPI GPU& IsStencilTestEnabled(bool value);

                /// <summary> Sets the shader pipeline that will be used by the GPU to render images. </summary>
                PlatformAPI GPU& Pipeline(IGraphicsPipeline* pipeline);
                /// <summary> Sets the projection transformation matrix that will be used by GPU shader pipeline. </summary>
                PlatformAPI GPU& Projection(ISpatialTransform* projection);
                /// <summary> Sets the 3D rendering scene that will be displayed for the user. </summary>
                PlatformAPI GPU& Scene(IScene* scene, int slot = 0);

                PlatformAPI GPU& Settings(const GraphicsSettings& value);
                /// <summary> Sets the framebuffer to which all subsequent rendering will occur. </summary>
                PlatformAPI GPU& Target(FrameBuffer* framebuffer, int slot = 0);
                /// <summary> Sets the view transformation matrix that will be used by the GPU shader pipeline. </summary>
                PlatformAPI GPU& View(ISpatialTransform* view);
                /// <summary> Sets the window that will be used to display the images in the render target. </summary>
                PlatformAPI GPU& Window(Window3D* window);



                /** CONSTRUCTOR **/
                PlatformAPI GPU();
                PlatformAPI GPU(GPU&& other) = delete;
                PlatformAPI GPU(const GPU& other) = delete;
                PlatformAPI ~GPU();



                /** RENDERING UTILITIES **/
                /// <summary> Clears the depth-stencil and render target buffers in preparation for a new render loop iteration. </summary>
                /// <param name="color"> The color value that will be used to nullify or replace all contents of the render target. </param>
                /// <remarks> This method should be among the first called within the rendering loop. </remarks>
                PlatformAPI void Clear(const Color4& color = Color4::White, float depth = 1.0f, int stencil = 0);
                /// <summary> Swaps the front and back rendering buffers, displaying the contents of the backbuffer to the user. </summary>
                /// <remarks>
                ///     On Windows, and in particular within DirectX, the rendering buffer associated with a window is often
                ///     called a 'swap-chain'. The same construct exists OpenGL, although the term 'swap-chain' is somewhat
                ///     less common in that domain. It represents two separate framebuffers on which rendering occurs that are
                ///     constantly being cycled or swapped with one another in order to present drawings on-screen to the user.
                ///     One of these framebuffers is called a 'front' buffer, while the other is called the 'back' buffer.
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
                PlatformAPI void Present();
                /// <summary> Executes the shader pipeline currently bound to the GPU. </summary>
                PlatformAPI void Execute();
                /// <summary> Performs any necessary updates to buffer objects currently bound to the GPU. </summary>
                PlatformAPI void Update();



                /** GENERAL UTILITIES **/
                PlatformAPI void Bind(const BufferBinding& buffer);
                PlatformAPI void Bind(int slot, const IBindable& element);
                /// <summary> Generates a human-readable string detailing the internal state of the GPU object and any OpenGL errors encountered. </summary>
                /// <remarks>
                ///     Calls to this method impose a significant performance penalty and therefore should only be made sparingly, if
                ///     at all. Prefer invoking this functionality only while debugging.
                /// </remarks>
                PlatformAPI string Report()                                                     const override;
                /// <summary> Determines whether a specific OpenGL extension is available on the current system. </summary>
                /// <returns> A Boolean <c>true</c> if the given extension is supported, or <c>false</c> otherwise. </returns>
                /// <param name="extension"> A string containing the name of extension for which support is being queried. </param>
                PlatformAPI bool SupportsExtension(const string& extension)                     const;
                /// <summary> Gets a list of all OpenGL extensions that are supported in the current environment. </summary>
                PlatformAPI List<string> QueryExtensions()                                      const;



                /** UNIFORM DATA ACCESSORS **/
                PlatformAPI int GetUniformID(const string& name)                                const;
                PlatformAPI void SetUniform(const string& name, const Color4& value)            const;
                PlatformAPI void SetUniform(const string& name, const ISpatialTransform& value) const;

            private:

                /** PROPERTY DATA **/
                Window3D*                   _renderWindow;
                IScene*                     _renderScene;
                GraphicsSettings            _settings;
                bool                        _updateFrameData;
                bool                        _updateSettings;



                /** PRIVATE DATA **/
                UniformBuffer<PerFrame>     PerFrameBuffer;



                /** PRIVATE UTILITIES **/
                void RestoreRenderingDefaults();
                string ReportErrors() const;
                void UpdateFrameData();
                void UpdateSettings();

        };
    }
}
