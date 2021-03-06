#include "Utilities.h"
#include "Math/Constants.h"
#include "Math/Math.h"
#include "Math/Matrix4x4.h"
#include "Spatial/Camera.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace Utilities
    {

        /** PROPERTIES **/
        Vector3 Camera::Forward() const
        {
            Update();
            return Vector3(-State(2, 0), -State(2, 1), -State(2, 2)).Normalize();
        }

        Vector3 Camera::Right() const
        {
            Update();
            return Vector3(State(0, 0), State(0, 1), State(0, 2)).Normalize();
        }

        Camera& Camera::Orientation(const Vector3& value)
        {
            _needsUpdate = true;

            _orientation.X = Math::Clamp(value.X, -Constants::HalfPi<float> + 0.001f, Constants::HalfPi<float> - 0.001f);
            _orientation.Y = wrap(value.Y, 0.0f, Constants::TwoPi<float> - 0.001f);
            _orientation.Z = wrap(value.Z, 0.0f, Constants::TwoPi<float> - 0.001f);
            
            return *this;
        }
        Camera& Camera::Position(const Vector3& value)
        {
            _needsUpdate = true;
            _position = value;
            return *this;
        }
        Camera& Camera::Scale(const Vector3& value)
        {
            _needsUpdate = true;
            _scale = value;
            return *this;
        }


        /** CONSTRUCTOR **/
        Camera::Camera(const Vector3& position, const Vector3& scale, const Vector3& orientation) :
            _needsUpdate(false),
            _orientation(orientation),
            _position(position),
            _scale(scale)
        {

        }



        /** UTILITIES **/
        Camera& Camera::Rotate(const Vector3& r)
        {
            return Orientation(Orientation() + r);
        }
        Camera& Camera::Translate(const Vector3& t)
        {
            return Position(Position() + t);
        }



        /** OPERATORS **/
        bool Camera::operator ==(const Camera& other) const
        {
            return ToMatrix4x4() == other.ToMatrix4x4();
        }


        /** PRIVATE UTILITIES **/
        /// <summary> Calculates the value for each element of the state matrix. </summary>
        /// <remarks>
        ///     Scale * Pitch * Yaw * Roll * Translation
        /// </remarks>
        void Camera::Update() const
        {
            if (!_needsUpdate) { return; }

            float cr, cp, cy, sr, sp, sy, w, h, d, x, y, z;
            w = _scale.X; h = _scale.Y; d = _scale.Z;
            x = -_position.X; y = -_position.Y; z = -_position.Z;
            cr = (float)cos(_orientation.Z); cp = (float)cos(_orientation.X); cy = (float)cos(_orientation.Y);
            sr = (float)sin(_orientation.Z); sp = (float)sin(_orientation.X); sy = (float)sin(_orientation.Y);

            State(0)  = (cr * cy * w);
            State(1)  = (cp * h * sr) + (cr * h * sp * sy);
            State(2)  = (d * sp * sr) - (cp * cr * d * sy);
                      
            State(4)  = -(cy * sr * w);
            State(5)  = (cp * cr * h) - (h * sp * sr * sy);
            State(6)  = (cr * d * sp) + (cp * d * sr * sy);
                      
            State(8)  = sy * w;
            State(9)  = -(cy * h * sp);
            State(10) = cp * cy * d;

            State(12) = (sy * w * z) + (cr * cy * w * x) - (cy * sr * w * y);
            State(13) = ( x * ((cp*h*sr) + (cr*h*sp*sy)) ) + ( y * ((cp*cr*h) - (h*sp*sr*sy)) ) - (cy*h*sp*z);
            State(14) = ( x * ((d*sp*sr) - (cp*cr*d*sy)) ) + ( y * ((cr*d*sp) + (cp*d*sr*sy)) ) + (cp*cy*d*z);

            _needsUpdate = false;
        }
    }
}