/* CHANGELOG
 * Written by Josh Grooms on 20160523
 */

#pragma once
#include "GL/OpenGLAPI.h"


namespace Cyclone
{
    namespace OpenGL
    {

        /* IBINDABLE - An interface used to specify the behavior of any entity that is bindable to a GPU rendering pipeline. */
        class OpenGLAPI IBindable
        {
            public:
                using uint = unsigned int;

                /** PROPERTIES **/
                /* ID - Gets the unique numeric identifier for this entity on the GPU. */
                virtual uint ID()                       const = 0;



                /** DESTRUCTOR **/
                virtual ~IBindable() { }



                /** BINDING UTILITIES **/
                /* BIND - Summarily attaches this entity and its associated resources to the rendering pipeline. */
                virtual void Bind(int slot = 0)         const = 0;
                /* BINDENTITY - Attaches this entity to the rendering pipeline. */
                virtual void BindEntity(int slot = 0)   const = 0;
                /* BINDRESOURCES - Attaches any resources associated with this entity to the rendering pipeline. */
                virtual void BindResources()            const = 0;

                /* UNBIND - Summarily detaches this entity and its associated resources from the rendering pipeline. */
                virtual void Unbind()                   const = 0;
                /* UNBINDENTITY - Detaches this entity from the rendering pipeline. */
                virtual void UnbindEntity()             const = 0;
                /* UNBINDRESOURCES - Detaches any resources associated with this entity from the rendering pipeline. */
                virtual void UnbindResources()          const = 0;

        };

    }
}