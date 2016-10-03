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
                float X()                                                       const { return _position.X; }
                float Y()                                                       const { return _position.Y; }
                float Z()                                                       const { return _position.Z; }

                float Pitch()                                                   const { return _orientation.X; }
                float Roll()                                                    const { return _orientation.Z; }
                float Yaw()                                                     const { return _orientation.Y; }

                const Vector3& Orientation()                                    const override { return _orientation; }
                const Vector3& Position()                                       const override { return _position; }
                const Vector3& Scale()                                          const override { return _scale; }


                Camera& X(float x)                                                       { return Position(x, Y(), Z()); }
                Camera& Y(float y)                                                       { return Position(X(), y, Z()); }
                Camera& Z(float z)                                                       { return Position(X(), Y(), z); }
                                                                                         
                Camera& Pitch(float p)                                                   { return Orientation(p, Yaw(), Roll()); }
                Camera& Roll(float r)                                                    { return Orientation(Pitch(), Yaw(), r); }
                Camera& Yaw(float y)                                                     { return Orientation(Pitch(), y, Roll()); }

                Camera& Orientation(float p, float y, float r)                           { return Orientation(Vector3(p, y, r)); }
                UtilitiesAPI Camera& Orientation(const Vector3& value)          override;
                Camera& Position(float x, float y, float z)                              { return Position(Vector3(x, y, z)); }
                UtilitiesAPI Camera& Position(const Vector3& value)             override;
                Camera& Scale(float x, float y, float z)                                 { return Scale(Vector3(x, y, z)); }
                UtilitiesAPI Camera& Scale(const Vector3& value)                override;

                Vector3 Backward()                                              const { return -Forward(); }
                UtilitiesAPI Vector3 Forward()                                  const;
                Vector3 Left()                                                  const { return -Right(); }
                UtilitiesAPI Vector3 Right()                                    const;
                
                
                UtilitiesAPI Camera& Translate(const Vector3& t)                override;
                UtilitiesAPI Camera& Rotate(const Vector3& r)                   override;


                UtilitiesAPI const Matrix4x4& ToMatrix4x4()                                  const override { Update(); return State; }




                UtilitiesAPI Camera();


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
