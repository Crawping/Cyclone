#include "Console.h"
#include "Texture.h"



/** CONSTRUCTORS & DESTRUCTOR **/
Texture::Texture(TextureFormats format, TextureTargets target) :
    _format(format),
    _handle(0),
    _id(0),
    _target(target)
{
    Create();
}
Texture::~Texture()
{
    MakeNonresident();
    if (_id)
        glDeleteTextures(1, &_id);
}



/** BINDING UTILITIES **/
void Texture::BindEntity(int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(Target(), ID());
}
void Texture::MakeNonresident()
{
    glMakeTextureHandleNonResidentARB(Handle());
}
void Texture::MakeResident()
{
    if (!_handle)
        _handle = glGetTextureHandleARB(_id);
    glMakeTextureHandleResidentARB(Handle());
}
void Texture::UnbindEntity() const
{
    glBindTexture(Target(), 0);
    glActiveTexture(GL_TEXTURE0);
}



/** TEXTURE UTILITIES **/
void Texture::GenerateMipmap()
{
    if (IsEmpty()) { return; }
    glGenerateTextureMipmap(ID());
}



/** PROTECTED UTILITIES **/
void Texture::Create()
{
    if (_id)
    {
        Console::WriteLine("A texture object already exists and must be deleted before attempting to create a new one.");
        return;
    }
    glCreateTextures(Target(), 1, &_id);
}
void Texture::Destroy()
{
    if (_id)
    {
        MakeNonresident();
        glDeleteTextures(1, &_id);
        _handle = 0;
        _id = 0;
    }
}
