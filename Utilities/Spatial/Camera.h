/* CHANGELOG
 * Written by Josh Grooms on 20160923
 */

#pragma once
#include "UtilitiesAPI.h"
#include "Interfaces/ITransformation3D.h"
#include "Math/Matrix4x4.h"



namespace Cyclone
{
    namespace Utilities
    {
        class Camera : public ITransformation3D
        {
            public:
                /// <summary> Gets the translation of the camera along the x-axis. </summary>
                float X()                                                       const { return _position.X; }
                /// <summary> Gets the translation of the camera along the y-axis. </summary>
                float Y()                                                       const { return _position.Y; }
                /// <summary> Gets the translation of the camera along the z-axis. </summary>
                float Z()                                                       const { return _position.Z; }
                
                /// <summary> Gets the camera's angle of rotation about the x-axis in radians. </summary>
                float Pitch()                                                   const { return _orientation.X; }
                /// <summary> Gets the camera's angle of rotation about the z-axis in radians. </summary>
                float Roll()                                                    const { return _orientation.Z; }
                /// <summary> Gets the camera's angle of rotation about the y-axis in radians. </summary>
                float Yaw()                                                     const { return _orientation.Y; }

                /// <summary> Gets the camera's (x, y, z) angles of rotation in radians. </summary>
                const Vector3& Orientation()                                    const override { return _orientation; }
                /// <summary> Gets the (x, y, z) translation components of the camera transformation matrix. </summary>
                const Vector3& Position()                                       const override { return _position; }
                /// <summary> Gets the (x, y, z) scaling components of the camera's transformation matrix. </summary>
                const Vector3& Scale()                                          const override { return _scale; }

                /// <summary> Sets the translation of the camera along the x-axis. </summary>
                Camera& X(float x)                                                       { return Position(x, Y(), Z()); }
                /// <summary> Sets the translation of the camera along the y-axis. </summary>
                Camera& Y(float y)                                                       { return Position(X(), y, Z()); }
                /// <summary> Sets the translation of the camera along the z-axis. </summary>
                Camera& Z(float z)                                                       { return Position(X(), Y(), z); }
                                                                                         
                /// <summary> Sets the camera's angle of rotation about the x-axis in radians. </summary>
                Camera& Pitch(float p)                                                   { return Orientation(p, Yaw(), Roll()); }
                /// <summary> Sets the camera's angle of rotation about the z-axis in radians. </summary>
                Camera& Roll(float r)                                                    { return Orientation(Pitch(), Yaw(), r); }
                /// <summary> Sets the camera's angle of rotation about the y-axis in radians. </summary>
                Camera& Yaw(float y)                                                     { return Orientation(Pitch(), y, Roll()); }

                Camera& Orientation(float p, float y, float r)                           { return Orientation(Vector3(p, y, r)); }
                UtilitiesAPI Camera& Orientation(const Vector3& value)          override;
                Camera& Position(float x, float y, float z)                              { return Position(Vector3(x, y, z)); }
                UtilitiesAPI Camera& Position(const Vector3& value)             override;
                Camera& Scale(float x, float y, float z)                                 { return Scale(Vector3(x, y, z)); }
                UtilitiesAPI Camera& Scale(const Vector3& value)                override;

                /// <summary> Gets a vector that points backward in 3D view space. </summary>
                /// <returns> A normalized vector pointing backward relative to the camera's current orientation. </returns>
                Vector3 Backward()                                              const { return -Forward(); }
                /// <summary> Gets a vector that points forward in 3D view space. </summary>
                /// <returns> A normalized vector pointing forward relative to the camera's current orientation. </returns>
                UtilitiesAPI Vector3 Forward()                                  const;
                /// <summary> Gets a vector that points left in 3D view space. </summary>
                /// <returns> A normalized vector pointing left relative to the camera's current orientation. </returns>
                Vector3 Left()                                                  const { return -Right(); }
                /// <summary> Gets a vector that points right in 3D view space. </summary>
                /// <returns> A normalized vector pointing right relative to the camera's current orientation. </returns>
                UtilitiesAPI Vector3 Right()                                    const;
                              


                /** CONSTRUCTOR **/
                UtilitiesAPI Camera();



                /** UTILITIES **/
                /// <summary> Sets the (x, y, z) angles of rotation for the transformation matrix relative to their current values. </summary>
                UtilitiesAPI Camera& Rotate(const Vector3& r)                   override;
                /// <summary> Sets the (x, y, z) translation components of the transformation matrix relative to their current values. </summary>
                UtilitiesAPI Camera& Translate(const Vector3& t)                override;
                /// <summary> Converts the camera transformation structure into an ordinary 4x4 transformation matrix. </summary>
                /// <returns> A reference to the transformation matrix that performs the camera's translation, scaling, and rotation operations. </returns>
                UtilitiesAPI const Matrix4x4& ToMatrix4x4()                     const override { Update(); return State; }

            private:

                /** PROPERTY DATA **/
                mutable bool    _needsUpdate;
                Vector3         _orientation;
                Vector3         _position;
                Vector3         _scale;


                /** DATA **/
                mutable Matrix4x4 State;


                /** UTILITIES **/
                void Update() const;
        };
    }
}
