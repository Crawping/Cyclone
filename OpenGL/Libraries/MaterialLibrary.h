/* CHANGELOG
 * Written by Josh Grooms on 20161125
 */

#pragma once
#include "Buffers/UniformData.h"
#include "Buffers/UniformMap.h"



namespace Cyclone
{
    namespace OpenGL
    {

        class MaterialLibrary : public UniformMap<int, MaterialData>
        {
            public:

                /** CONSTRUCTOR **/
                OpenGLAPI MaterialLibrary();



                OpenGLAPI int Add(const MaterialData& material);



            //private:

                
        };
    }
}
