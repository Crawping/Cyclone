/* CHANGELOG
 * Written by Josh Grooms on 20170417
 */

#pragma once



namespace Cyclone
{
    namespace OpenGL
    {

        //struct IResourceData { };

        class IGraphicsResource
        {
            public:

                //virtual const IResourceData& Data()         const = 0;

                virtual ~IGraphicsResource() { }

                virtual IGraphicsResource* CreateView()     const = 0;

        };
    }
}
