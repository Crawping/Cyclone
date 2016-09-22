/* CHANGELOG
 * Written by Josh Grooms on 20160828
 */

#pragma once
#include "EnumerationsGL.h"
#include "TypeDefinitions.h"
#include "Interfaces/IVertex.h"
#include "Math/Array.h"
#include "Math/Vector3.h"



namespace Cyclone
{
    namespace OpenGL
    {

        using namespace Cyclone::Utilities;

        /// <summary> A data structure that defines a single component of a vertex. </summary>
        struct VertexAttribute
        {
            /// <summary> The number of elements present in the attribute. </summary>
            uint            Count;
            /// <summary> The numeric type of each element present in the attribute. </summary>
            NumericFormats  Format;
            /// <summary> The name of the attribute. </summary>
            string          Name;
            /// <summary> The byte offset into the vertex structure at which data for the attribute can be found. </summary>
            uint            Offset;

            /// <summary> Constructs an empty vertex attribute with no elements, no name, and no offset. </summary>
            VertexAttribute() :
                Count(0),
                Format(NumericFormats::Float),
                Name(""),
                Offset(0)
            {

            }
            /// <summary> Constructs a new vertex attribute used to define a vertex layout. </summary>
            /// <param name="count"> The number of elements present in the attribute. </param>
            /// <param name="format"> The numeric type of each element present in the attribute. </param>
            /// <param name="name"> The name of this attribute. </param>
            /// <param name="offset"> The byte offset into the vertex structure at which the data for the attribute can be found. </param>
            VertexAttribute(uint count, NumericFormats format, const string& name, uint offset) :
                Count(count),
                Format(format),
                Name(name),
                Offset(offset)
            {

            }
        };

        
        /// <summary> A collection of standardized vertex definitions. </summary>
        namespace Vertex
        {
            /// <summary> A structure defining a vertex with positional and texture data only. </summary>
            struct Simple : public IVertex
            {   

                /** DATA **/
                /// <summary> The (x, y, z) position of the vertex in model space. </summary>
                Vector3 Position;
                /// <summary> The (u, v) texture coordinates associated with the vertex. </summary>
                Vector2 UV;
                
                Vector<VertexAttribute> Layout() const override
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

            /// <summary> A structure that defines a vertex consisting of positional, normal, and texture data. </summary>
            struct Standard : public IVertex
            {
                /** DATA **/
                /// <summary> The (x, y, z) position of the vertex in model space. </summary>
                Vector3 Position;
                /// <summary> The (x, y, z) direction of a vector that is perpendicular to the surface surrounding the vertex. </summary>
                Vector3 Normal;
                /// <summary> The (u, v) texture coordinates associated with the vertex. </summary>
                Vector2 UV;

                Vector<VertexAttribute> Layout() const override
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
