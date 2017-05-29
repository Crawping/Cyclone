/* CHANGELOG
 * Written by Josh Grooms on 20160828
 */

#pragma once
#include "EnumerationsGL.h"
#include "Collections/Array.h"
#include "Collections/String.h"
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
            String          Name;
            /// <summary> The byte offset into the vertex structure at which data for the attribute can be found. </summary>
            uint            Offset;



            /** OPERATORS **/
            constexpr bool operator ==(const VertexAttribute& other) const
            {
                return 
                    (Count == other.Count)      && 
                    (Format == other.Format)    && 
                    (Name == other.Name)        && 
                    (Offset == other.Offset);
            }
            constexpr bool operator !=(const VertexAttribute& other) const { return !operator ==(other); }
        };

        
        /// <summary> A structure that defines a vertex consisting of positional, normal, and texture data. </summary>
        struct Vertex
        {

            /** DATA **/
            /// <summary> The (x, y, z) position of the vertex in model space. </summary>
            Vector3 Position;
            /// <summary> The (x, y, z) direction of a vector that is perpendicular to the surface surrounding the vertex. </summary>
            Vector3 Normal;
            /// <summary> The (u, v) texture coordinates associated with the vertex. </summary>
            Vector2 UV;



            /** STATIC DATA **/
            constexpr static Array<VertexAttribute, 3> Layout()
            {
                return
                {
                    { 3, NumericFormats::Float, "Position", offsetof(Vertex, Position) },
                    { 3, NumericFormats::Float, "Normal", offsetof(Vertex, Normal) },
                    { 2, NumericFormats::Float, "UV", offsetof(Vertex, UV) },
                };
            }



            /** CONSTRUCTORS **/
            /// <summary> Constructs a default 3D geometric vertex that can be used on the GPU. </summary>
            constexpr Vertex():
                Position(0.0f),
                Normal(0.0f),
                UV(0.0f)
            {

            }
            /// <summary> Constructs a 3D polygon vertex that can used on the GPU. </summary>
            /// <param name="position"> The desired position of the vertex in 3D space. </param>
            /// <param name="normal"> The desired direction of the vector considered normal to the vertex. </param>
            /// <param name="uv"> The mapping of the vertex into 2D texture UV space. </param>
            constexpr Vertex(const Vector3& position, const Vector3& normal, const Vector2& uv) :
                Position(position),
                Normal(normal),
                UV(uv)
            {

            }

            constexpr Vertex(const Vector3& position, const Vector3& normal, const Vector3& uv) :
                Position(position),
                Normal(normal),
                UV((Vector2)uv)
            {

            }

            constexpr Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) :
                Position(x, y, z),
                Normal(nx, ny, nz),
                UV(u, v)
            {

            }

            constexpr Vertex(float x, float y, float z, float u = 0.0f, float v = 0.0f):
                Position(x, y, z),
                Normal(0.0f),
                UV(u, v)
            {

            }



            /** OPERATORS **/
            constexpr bool operator ==(const Vertex& other) const
            {
                return
                    (Position == other.Position)    && 
                    (Normal == other.Normal)        && 
                    (UV == other.UV);
            }
            constexpr bool operator !=(const Vertex& other) const { return !operator ==(other); }

        };

    }
}
