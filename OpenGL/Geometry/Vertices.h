/* CHANGELOG
 * Written by Josh Grooms on 20160828
 */

#pragma once
#include "EnumerationsGL.h"
#include "TypeDefinitions.h"
#include "Math/Array.h"
#include "Math/Vector3.h"
#include <string>




namespace Cyclone
{
    namespace OpenGL
    {
        using namespace Cyclone::Utilities;

        struct VertexAttribute
        {
            uint            Count;
            NumericFormats  Format;
            string          Name;
            uint            Offset;

            VertexAttribute() :
                Count(0),
                Name(""),
                Offset(0)
            {

            }

            VertexAttribute(uint count, NumericFormats format, const string& name, uint offset) :
                Count(count),
                Format(format),
                Name(name),
                Offset(offset)
            {

            }
        };

        struct IVertex
        {

            virtual Array<VertexAttribute> Layout() const = 0;

            virtual ~IVertex() { }

        };


        namespace Vertex
        {
            struct Simple : public IVertex
            {   

                Vector3 Position;
                Vector2 UV;
                
                Array<VertexAttribute> Layout() const override
                {
                    return
                    {
                        VertexAttribute(3, NumericFormats::Float, "Position", offsetof(Simple, Position)),
                        VertexAttribute(2, NumericFormats::Float, "UV", offsetof(Simple, UV)),
                    };
                }
                
                constexpr Simple()                                                          : Position(0.0f), UV(0.0f) { }
                constexpr Simple(const Vector3& position, const Vector2& uv)                : Position(position), UV(uv) { }
                constexpr Simple(float x, float y, float z, float u = 0.0f, float v = 0.0f) : Position(x, y, z), UV(u, v) { }

            };

            struct Standard : public IVertex
            {
                Vector3 Position;
                Vector3 Normal;
                Vector2 UV;

                Array<VertexAttribute> Layout() const override
                {
                    return
                    {
                        VertexAttribute(3, NumericFormats::Float, "Position", offsetof(Standard, Position)),
                        VertexAttribute(3, NumericFormats::Float, "Normal", offsetof(Standard, Normal)),
                        VertexAttribute(2, NumericFormats::Float, "UV", offsetof(Standard, UV)),
                    };
                }

                constexpr Standard() :
                    Position(0.0f),
                    Normal(0.0f),
                    UV(0.0f)
                {

                }

                constexpr Standard(const Vector3& position, const Vector3& normal, const Vector2& uv) :
                    Position(position),
                    Normal(normal),
                    UV(uv)
                {

                }

                constexpr Standard(float x, float y, float z, float nx, float ny, float nz, float u, float v) :
                    Position(x, y, z),
                    Normal(nx, ny, nz),
                    UV(u, v)
                {

                }

                constexpr Standard(float x, float y, float z, float u = 0.0f, float v = 0.0f) :
                    Position(x, y, z),
                    Normal(0.0f),
                    UV(u, v)
                {

                }

            };

        }


    }
}
