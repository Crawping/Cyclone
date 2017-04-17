/* CHANGELOG
 * Written by Josh Grooms on 20170417
 */

#pragma once



namespace Cyclone
{
    namespace OpenGL
    {
        class IGraphicsResource
        {
            public:

                virtual ~IGraphicsResource() { }

                virtual IGraphicsResource* CreateView()     const = 0;

        };
    }
}
