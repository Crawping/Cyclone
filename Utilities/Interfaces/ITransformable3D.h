/* CHANGELOG
 * Written by Josh Grooms on 20170528
 */

#pragma once
#include "Math/Vector3.h"



namespace Cyclone
{
    namespace Utilities
    {

        class ITransformable3D
        {

            public:
                using IT3D = ITransformable3D;

                /** POSITIONAL PROPERTIES **/
                /// <summary> Gets the position of the entity along the world x-axis. </summary>
                virtual float X()                           const { return Position().X; }
		        /// <summary> Gets the position of the entity along the world y-axis. </summary>
                virtual float Y()                           const { return Position().Y; }
		        /// <summary> Gets the position of the entity along the world z-axis. </summary>
                virtual float Z()                           const { return Position().Z; }

		        /// <summary> Sets the position of the entity along the world x-axis. </summary>
                virtual IT3D& X(float x)                    { return Position(x, Y(), Z()); }
		        /// <summary> Sets the position of the entity along the world y-axis. </summary>
                virtual IT3D& Y(float y)                    { return Position(X(), y, Z()); }
		        /// <summary> Sets the position of the entity along the world z-axis. </summary>
                virtual IT3D& Z(float z)                    { return Position(X(), Y(), z); }



                /** ROTATIONAL PROPERTIES **/
                /// <summary> Gets the angle of rotation about the x-axis in radians. </summary>
                virtual float Pitch()                       const { return Orientation().X; }
                /// <summary> Gets the angle of rotation about the z-axis in radians. </summary>
                virtual float Roll()                        const { return Orientation().Z; }
                /// <summary> Gets the angle of rotation about the y-axis in radians. </summary>
                virtual float Yaw()                         const { return Orientation().Y; }

                /// <summary> Sets the angle of rotation about the x-axis in radians. </summary>
                virtual IT3D& Pitch(float p)                { return Orientation(p, Yaw(), Roll()); }
                /// <summary> Sets the angle of rotation about the z-axis in radians. </summary>
                virtual IT3D& Roll(float r)                 { return Orientation(Pitch(), Yaw(), r); }
                /// <summary> Sets the angle of rotation about the y-axis in radians. </summary>
                virtual IT3D& Yaw(float y)                  { return Orientation(Pitch(), y, Roll()); }



                /** SCALING PROPERTIES **/
		        /// <summary> Gets the size of the entity along the z-axis. </summary>
                virtual float Depth()                       const { return Scale().Z; }
		        /// <summary> Gets the size of the entity along the y-axis. </summary>
                virtual float Height()                      const { return Scale().Y; }
		        /// <summary> Gets the size of the entity along the x-axis. </summary>
                virtual float Width()                       const { return Scale().X; }

		        /// <summary> Sets the size of the entity along the z-axis. </summary>
                virtual IT3D& Depth(float z)                { return Scale(Width(), Height(), z); }
		        /// <summary> Sets the size of the entity along the y-axis. </summary>
                virtual IT3D& Height(float y)               { return Scale(Width(), y, Depth()); }
		        /// <summary> Sets the size of the entity along the x-axis. </summary>
                virtual IT3D& Width(float x)                { return Scale(x, Height(), Depth()); }


                
                /** BATCH SPATIAL PROPERTIES **/
                /// <summary> Gets the (x, y, z) rotation angles for the entity in world space. </summary>
                virtual const Vector3& Orientation()                        const = 0;
                /// <summary> Gets the (x, y, z) position of the entity in world space. </summary>
                virtual const Vector3& Position()                           const = 0;
                /// <summary> Gets the (x, y, z) scaling of the entity in world space. </summary>
                virtual const Vector3& Scale()                              const = 0;

                /// <summary> Sets the (x, y, z) rotation of for the entity in world space. </summary>
                virtual IT3D& Orientation(const Vector3& value)             = 0;
                /// <summary> Sets the (x, y, z) rotation angles of the entity in world space. </summary>
                /// <param name="p"> The pitch, or rotation about the x-axis, in radians. </param>
                /// <param name="y"> The yaw, or rotation about the y-axis, in radians. </param>
                /// <param name="r"> The roll, or rotation about the z-axis, in radians. </param>
                virtual IT3D& Orientation(float p, float y, float r)        { return Orientation(Vector3(p, y, r)); }
                /// <summary> Sets the (x, y, z) position of the entity in world space. </summary>
                virtual IT3D& Position(const Vector3& value)                = 0;
                /// <summary> Sets the (x, y, z) position of the entity in world space. </summary>
                virtual IT3D& Position(float x, float y, float z = 0.0f)    { return Position(Vector3(x, y, z)); }
                /// <summary> Sets the (x, y, z) scaling of the entity in world space. </summary>
                virtual IT3D& Scale(const Vector3& value)                   = 0;
                /// <summary> Sets the (x, y, z) scaling of the entity in world space. </summary>
                virtual IT3D& Scale(float x, float y, float z = 1.0f)       { return Scale(Vector3(x, y, z)); }

                

                /** DESTRUCTOR **/
                virtual ~ITransformable3D() { }



                /** UTILITIES **/
                /// <summary> Sets the (x, y, z) rotation angles for the entity relative to their current values. </summary>
                virtual IT3D& Rotate(const Vector3& value)
                {
                    Orientation(Orientation() + value);
                    return *this;
                }
                /// <summary> Sets the (x, y, z) rotation angles for the entity relative to their current values. </summary>
                virtual IT3D& Rotate(float x, float y, float z)             { return Rotate(Vector3(x, y, z)); }
                /// <summary> Sets the position of the entity in 3D space relative to its current position. </summary>
                virtual IT3D& Translate(const Vector3& value)
                {
                    Position(Position() + value);
                    return *this;
                }
                /// <summary> Sets the position of the entity in 3D space relative to its current position. </summary>
                virtual IT3D& Translate(float x, float y, float z)          { return Translate(Vector3(x, y, z)); }
                
        };

    }
}
