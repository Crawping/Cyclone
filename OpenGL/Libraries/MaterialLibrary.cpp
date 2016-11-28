#include "Libraries/MaterialLibrary.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** CONSTRUCTOR **/
        MaterialLibrary::MaterialLibrary()
        {

        }



        int MaterialLibrary::Add(const MaterialData& material)
        {
            for (int key : Keys())
                if (material == Get(key))
                    return key;

            int idx = Count();
            Set(idx, material);
            return idx;
        }
    }
}