/* CHANGELOG
 * Written by Josh Grooms on 20150905
 */

#define _USE_MATH_DEFINES
#include "Math/Constants.h"
#include "Spatial/Transform.h"
#include "Spatial/Volume.h"
#include <cmath>
#include <sstream>



namespace Cyclone
{
    namespace Utilities
    {

        /** PROPERTIES **/
        Transform3D& Transform3D::Orientation(const Vector3& value)
        {
            _orientation = value;
            _needsUpdate = true;
            return *this;
        }
        Transform3D& Transform3D::Position(const Vector3& value)
        {
            _position = value;
            _needsUpdate = true;
            return *this;
        }
        Transform3D& Transform3D::Scale(const Vector3& value)
        {
            _size = value;
            _needsUpdate = true;
            return *this;
        }



        /** CONSTRUCTORS **/
        Transform3D::Transform3D() :
            Transform3D(0.0f, 1.0f, 0.0f)
        {

        }
        Transform3D::Transform3D(const Transform3D& other) :
            _needsUpdate(other._needsUpdate),
            _orientation(other._orientation),
            _position(other._position),
            _size(other._size),
            State(other.State)
        {

        }
        Transform3D::Transform3D(const float* m) :
            Transform3D(Vector3(m[12], m[13], m[14]), Vector3(m[0], m[5], m[10]), 0.0f)
        {

        }
        Transform3D::Transform3D(const Vector3& position, const Vector3& size, const Vector3& angles) :
            _needsUpdate(true),
            _orientation(angles),
            _position(position),
            _size(size)
        {
            Update();
        }



        /** STATIC CONSTRUCTORS **/
        Transform3D Transform3D::Decompose(const Matrix4x4& transform)
        {
            Vector3 xbasis(transform(0, 0), transform(1, 0), transform(2, 0));
            Vector3 ybasis(transform(0, 1), transform(1, 1), transform(2, 1));
            Vector3 zbasis(transform(0, 2), transform(1, 2), transform(2, 2));

            Vector3 position(transform(0, 3), transform(1, 3), transform(2, 3));
            Vector3 scale(xbasis.Norm(), ybasis.Norm(), zbasis.Norm());

            Matrix4x4 rotation(transform);
            for (uint a = 0; a < 3; a++)
                for (uint b = 0; b < 3; b++)
                    rotation(a, b) /= scale(b);

            Vector3 orientation(0, -asinf(rotation(2, 0)), 0);
            float cy = cosf(orientation.Y);

            orientation.X = atan2f(rotation(2, 1) / cy, rotation(2, 2) / cy);
            orientation.Z = atan2f(rotation(1, 0) / cy, rotation(0, 0) / cy);

            return Transform3D(position, scale, orientation);
        }
        Transform3D Transform3D::OrthographicProjection(const Volume& displayVolume)
        {
            Transform3D p;
            p.State(0)  = 2.0f / displayVolume.Width;
            p.State(5)  = 2.0f / displayVolume.Height;
            p.State(10) = -2.0f / displayVolume.Depth;
            p.State(12) = -2.0f * displayVolume.Right() / displayVolume.Width;
            p.State(13) = -2.0f * displayVolume.Top() / displayVolume.Height;
            p.State(14) = -2.0f * displayVolume.Front() / displayVolume.Depth;

            p._position = Vector3(p.State(12), p.State(13), p.State(14));
            p._size = Vector3(p.State(0), p.State(5), p.State(10));

            return p;
        }
        Transform3D Transform3D::PerspectiveProjection(const Volume& displayVolume)
        {
            Transform3D p;

            p.State[0]  =  2.0f * displayVolume.Back() / displayVolume.Width;
            p.State[5]  =  2.0f * displayVolume.Back() / displayVolume.Height;
            p.State[8]  =  (displayVolume.Left() + displayVolume.Right()) / displayVolume.Width;
            p.State[9]  =  (displayVolume.Bottom() + displayVolume.Top()) / displayVolume.Height;
            p.State[10] = -(displayVolume.Front() + displayVolume.Back()) / displayVolume.Depth;
            p.State[11] = -1.0f;
            p.State[14] = -2.0f * displayVolume.Front() * displayVolume.Back() / displayVolume.Depth;
            p.State[15] =  0.0f;

            p._position = Vector3(p.State[12], p.State[13], p.State[14]);
            p._size     = Vector3(p.State[0], p.State[5], p.State[10]);

            return p;
        }
        Transform3D Transform3D::PerspectiveProjection(float fov, float aspect, float znear, float zfar)
        {
            float hHeight = znear * tan(fov * Constants::Pi<double> / 360.0);
            float hWidth = hHeight * aspect;

            Vector3 position(-hWidth, -hHeight, znear);
            Vector3 size(2.0f * hWidth, 2.0f * hHeight, zfar - znear);

            return PerspectiveProjection(Volume(position, size));
        }
        Transform3D Transform3D::Rotation(const Vector3& angles)
        {
            Transform3D r;
            float cr, cp, cy, sr, sp, sy;
            cr = (float)cos(angles.Z); cp = (float)cos(angles.X); cy = (float)cos(angles.Y);
            sr = (float)sin(angles.Z); sp = (float)sin(angles.X); sy = (float)sin(angles.Y);

            r._orientation = angles;

            r.State(0)  = (cr * cy);
            r.State(1)  = (cy * sr);
            r.State(2)  = (-sy);

            r.State(4)  = (cr * sp * sy) - (cp * sr);
            r.State(5)  = (cp * cr) + (sp * sr * sy);
            r.State(6)  = (cy * sp);

            r.State(8)  = (sp * sr) + (cp * cr * sy);
            r.State(9)  = (cp * sr * sy) - (cr * sp);
            r.State(10) = (cp * cy);

            return r;
        }
        Transform3D Transform3D::Rotation(float pitch, float yaw, float roll)
        {
            return Rotation(Vector3(pitch, yaw, roll));
        }
        Transform3D Transform3D::Scaling(const Vector3& size)
        {
            Transform3D s;
            s._size = size;

            s.State[0]  = size.X;
            s.State[5]  = size.Y;
            s.State[10] = size.Z;

            return s;
        }
        Transform3D Transform3D::Scaling(float x, float y, float z)
        {
            return Scaling(Vector3(x, y, z));
        }
        Transform3D Transform3D::Translation(const Vector3& position)
        {
            Transform3D t;
            t._position = position;

            t.State[12] = position.X;
            t.State[13] = position.Y;
            t.State[14] = position.Z;
            return t;
        }
        Transform3D Transform3D::Translation(float x, float y, float z)
        {
            return Translation(Vector3(x, y, z));
        }



        /** UTILITIES **/
        Transform3D Transform3D::Inverse()                          const
        {
            Update();
            return Transform3D::Decompose(State.Inverse());
        }
        string Transform3D::Report()                                const
        {
            Update();
            std::stringstream msg;
            msg << "Transformation Matrix Details:\n" << State.ToString();
            return msg.str();
        }
        Transform3D& Transform3D::Rotate(const Vector3& value)
        {
            IT3D::Rotate(value);
            return *this;
        }
        const float* Transform3D::ToArray()                         const
        {
            Update();
            return State.ToArray();
        }
        const Matrix4x4& Transform3D::ToMatrix4x4()                 const
        {
            Update();
            return State;
        }
        Transform3D& Transform3D::Translate(const Vector3& value)
        {
            IT3D::Translate(value);
            return *this;
        }



        /** OPERATORS **/
        Transform3D Transform3D::operator *(const Transform3D& other) const
        {
            return Transform3D::Decompose(ToMatrix4x4() * other.ToMatrix4x4());
        }

        bool Transform3D::operator ==(const Transform3D& other)     const
        {
            if (this == (const Transform3D*) &other)
                return true;

            const float* leftState = ToArray();
            const float* rightState = other.ToArray();

            for (int a = 0; a < 16; a++)
                if (leftState[a] != rightState[a])
                    return false;

            return true;
        }



        /** PRIVATE UTILITIES **/
        /// <summary> Calculates the value for each element of the state matrix. </summary>
        /// <remarks>
        ///     This method effectively performs matrix multiplication to concatenate different affine transformations and does so in
        ///     a single pass, without actually generating and multiplying the component matrices. However, under that model, the
        ///     calculations performed here would correspond with multiplying transformation matrices in the following order:
        ///
        ///         Translation * Roll * Yaw * Pitch * Scale
        ///
        ///     The equations used in this method were derived using MATLAB.
        /// </remarks>
        void Transform3D::Update()                                const
        {
            if (!_needsUpdate) { return; }

            float cr, cp, cy, sr, sp, sy, w, h, d, x, y, z;
            w = _size.X; h = _size.Y; d = _size.Z;
            x = _position.X; y = _position.Y; z = _position.Z;
            cr = (float)cos(_orientation.Z); cp = (float)cos(_orientation.X); cy = (float)cos(_orientation.Y);
            sr = (float)sin(_orientation.Z); sp = (float)sin(_orientation.X); sy = (float)sin(_orientation.Y);

            State(0)  = (cr * cy * w);
            State(1)  = (cy * sr * w);
            State(2)  = (-sy * w);

            State(4)  = -h * ((cp * sr) - (cr * sp * sy));
            State(5)  = h * ((cp * cr) + (sp * sr * sy));
            State(6)  = (h * cy * sp);

            State(8)  = d * ((sp * sr) + (cp * cr * sy));
            State(9)  = -d * ((cr * sp) - (cp * sr * sy));
            State(10) = (cp * cy * d);

            State(12) = x;
            State(13) = y;
            State(14) = z;

            _needsUpdate = false;
        }

    }
}
