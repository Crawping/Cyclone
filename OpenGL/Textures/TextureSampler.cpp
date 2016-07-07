#include "OpenGL.h"
#include "TextureSampler.h"
#include <sstream>



TextureSampler::TextureSampler() :
    BorderColor(Color4::Transparent),
    EdgeWrap(WrapModes::ClampToBorder),
    LOD(0),
    MagnifyFilter(TextureFilters::Linear),
    MaxLOD(5),
    MinifyFilter(TextureFilters::Linear),
    MinLOD(0)
{

}
void TextureSampler::Bind() const
{
    Color4 color(BorderColor);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color.ToArray());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, EdgeWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, EdgeWrap);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, LOD);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagnifyFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, MaxLOD);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinifyFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, MinLOD);
}
string TextureSampler::Report() const
{
    std::stringstream msg;
    msg << "Texture Sampler Description:\n" <<
           "\tBorder Color:     "   <<
                BorderColor.R       << " " <<
                BorderColor.G       << " " <<
                BorderColor.B       << " " <<
                BorderColor.A                           << "\n" <<
           "\tEdge Wrap:        "   << EdgeWrap         << "\n" <<
           "\tLOD:              "   << LOD              << "\n" <<
           "\tMagnify Filter:   "   << MagnifyFilter    << "\n" <<
           "\tMaximum LOD:      "   << MaxLOD           << "\n" <<
           "\tMinify Filter:    "   << MinifyFilter     << "\n" <<
           "\tMinimum LOD:      "   << MinLOD           << "\n";

    return msg.str();
}


