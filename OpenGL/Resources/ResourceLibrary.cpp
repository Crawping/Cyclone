#include "Resources/ResourceLibrary2.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** CONSTRUCTOR & DESTRUCTOR **/
        ResourceLibrary2::ResourceLibrary2()
        {
            _buffers.Insert("Null", nullptr);
            _geometry.Insert("Null", nullptr);
            _materials.Insert("Null", nullptr);
            _pipelines.Insert("Null", nullptr);
            _renderables.Insert("Null", nullptr);
            _textures.Insert("Null", nullptr);
        }
        ResourceLibrary2::~ResourceLibrary2()
        {
            for (auto v : _buffers.Values())        { delete v; }
            for (auto v : _geometry.Values())       { delete v; }
            for (auto v : _materials.Values())      { delete v; }
            for (auto v : _pipelines.Values())      { delete v; }
            for (auto v : _renderables.Values())    { delete v; }
            for (auto v : _textures.Values())       { delete v; }
        }

    }
}