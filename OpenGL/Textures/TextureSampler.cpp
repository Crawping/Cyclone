#include "GL/OpenGL.h"
#include "Textures/TextureSampler.h"
#include <sstream>



namespace Cyclone
{
    namespace OpenGL
    {

        /** PROPERTIES **/
        TextureSampler& TextureSampler::BorderColor(const Color4& value)
        {
            _borderColor = value;
            _needsUpdate = true;
            return *this;
        }
        TextureSampler& TextureSampler::EdgeWrap(WrapModes value)
        {
            _edgeWrap = value;
            _needsUpdate = true;
            return *this;
        }
        TextureSampler& TextureSampler::LOD(int value)
        {
            _lod = value;
            _needsUpdate = true;
            return *this;
        }
        TextureSampler& TextureSampler::MagnifyFilter(TextureFilters value)
        {
            _magnifyFilter = value;
            _needsUpdate = true;
            return *this;
        }
        TextureSampler& TextureSampler::MaxLOD(int value)
        {
            _maxLOD = value;
            _needsUpdate = true;
            return *this;
        }
        TextureSampler& TextureSampler::MinifyFilter(TextureFilters value)
        {
            _minifyFilter = value;
            _needsUpdate = true;
            return *this;
        }
        TextureSampler& TextureSampler::MinLOD(int value)
        {
            _minLOD = value;
            _needsUpdate = true;
            return *this;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        TextureSampler::TextureSampler() :
            _id(0),
            _lod(0),
            _maxLOD(0),
            _minLOD(0),
            _needsUpdate(true)
        {
            glCreateSamplers(1, &_id);
        }
        TextureSampler::~TextureSampler()
        {
            if (_id)    glDeleteSamplers(1, &_id);
        }



        /** UTILITIES **/
        void TextureSampler::Bind(int slot)         const
        {
            BindEntity(slot);
            BindResources();
        }
        void TextureSampler::BindEntity(int slot)   const
        {
            Update();
            glBindSampler(slot, ID());
        }
        void TextureSampler::BindResources()        const
        {

        }
        void TextureSampler::Unbind()               const
        {
            UnbindResources();
            UnbindEntity();
        }
        void TextureSampler::UnbindEntity()         const
        {

        }
        void TextureSampler::UnbindResources()      const
        {

        }
        void TextureSampler::Update() const
        {
            if (!_needsUpdate) return;
            glSamplerParameterfv(ID(), GL_TEXTURE_BORDER_COLOR, BorderColor().ToArray());
            glSamplerParameteri(ID(), GL_TEXTURE_WRAP_S, EdgeWrap());
            glSamplerParameteri(ID(), GL_TEXTURE_WRAP_T, EdgeWrap());
            glSamplerParameteri(ID(), GL_TEXTURE_BASE_LEVEL, LOD());
            glSamplerParameteri(ID(), GL_TEXTURE_MAG_FILTER, MagnifyFilter());
            glSamplerParameteri(ID(), GL_TEXTURE_MAX_LOD, MaxLOD());
            glSamplerParameteri(ID(), GL_TEXTURE_MIN_FILTER, MinifyFilter());
            glSamplerParameteri(ID(), GL_TEXTURE_MIN_LOD, MinLOD());

            _needsUpdate = false;
        }

    }
}
