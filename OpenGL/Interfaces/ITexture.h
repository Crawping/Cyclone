/* CHANGELOG
 * Written by Josh Grooms on 20170414
 */

#pragma once
#include "EnumerationsGL.h"
#include "Interfaces/IBindable.h"
#include "Interfaces/IGraphicsResource.h"



namespace Cyclone
{
    namespace OpenGL
    {
        /// <summary> An interface that represents a generalized GPU texture resource. </summary>
        class ITexture : 
            public virtual IBindable
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets an enumerator that describes the format of the data stored within the texture. </summary>
                virtual TextureFormats Format()     const = 0;
                /// <summary> Gets the direct handle reference of the texture on the GPU. </summary>
                virtual ulong Handle()              const = 0;
                /// <summary> Gets whether the texture has any zero-length dimensions. </summary>
                virtual bool IsEmpty()              const = 0;
                /// <summary> Gets an enumerator that describes the type and dimensionality of the texture. </summary>
                virtual TextureTargets Target()     const = 0;

                virtual ~ITexture() { }
        };
    }
}