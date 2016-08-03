/* CHANGELOG
 * Written by Josh Grooms on 20160523
 */

#pragma once
#include "GL/OpenGLAPI.h"


namespace Cyclone
{
    namespace OpenGL
    {

        /// <summary> An interface used to specify the behavior of any entity that is bindable as a GPU resource. </summary>
        class OpenGLAPI IBindable
        {
            public:
                using uint = unsigned int;

                /** PROPERTIES **/
                /// <summary> Gets the unique numeric identifier for this entity on the GPU. </summary>
                virtual uint ID()                       const = 0;



                /** DESTRUCTOR **/
                virtual ~IBindable() { }



                /** BINDING UTILITIES **/
                /// <summary> Summarily attaches this entity and its associated resources to the rendering pipeline. </summary>
                virtual void Bind(int slot = 0)         const = 0;
                /// <summary> Attaches this entity to the rendering pipeline. </summary>
                virtual void BindEntity(int slot = 0)   const = 0;
                /// <summary> Attaches any resources associated with this entity to the rendering pipeline. </summary>
                virtual void BindResources()            const = 0;

                /// <summary> Summarily detaches this entity and its associated resources from the rendering pipeline. </summary>
                virtual void Unbind()                   const = 0;
                /// <summary> Detaches this entity from the rendering pipeline. </summary>
                virtual void UnbindEntity()             const = 0;
                /// <summary> Detaches any resources associated with this entity from the rendering pipeline. </summary>
                virtual void UnbindResources()          const = 0;

        };


        struct OpenGLAPI GraphicsBinding
        {
            const IBindable&    Entity;
            int                 Index;
        };
    }
}