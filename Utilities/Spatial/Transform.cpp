/* CHANGELOG
 * Written by Josh Grooms on 20150905
 */

#define _USE_MATH_DEFINES
#include "Constants.h"
#include "Transform.h"
#include "Volume.h"
#include <cmath>
#include <sstream>



namespace Cyclone
{
    namespace Utilities
    {
        /** CONSTRUCTORS **/
        Transform::Transform() :
            _size(Vector3::One),
            _updateFlag(false)
        {

        }        
        Transform::Transform(const Transform& other) :
            _orientation(other._orientation),
            _position(other._position),
            _size(other._size),
            _updateFlag(other._updateFlag),
            State(other.State)
        {

        }
        Transform::Transform(const float* m) :
            _position(m[12], m[13], m[14]),
            _size(m[0], m[5], m[10]),
            _updateFlag(false),
            State(m)
        {

        }
        Transform::Transform(const Vector3& position, const Vector3& size, const Vector3& angles) :
            _orientation(angles),
            _position(position),
            _size(size),
            _updateFlag(true)
        {
            UpdateState();
        }



        /** STATIC CONSTRUCTORS **/
        Transform Transform::PerspectiveProjection(const Volume& displayVolume)
        {
            Transform p;

            p.State[0]  = 2.0f * displayVolume.Front() / displayVolume.Width;
            p.State[5]  = 2.0f * displayVolume.Front() / displayVolume.Height;
            p.State[8]  = (displayVolume.Left() + displayVolume.Right()) / displayVolume.Width;
            p.State[9]  = (displayVolume.Bottom() + displayVolume.Top()) / displayVolume.Height;
            p.State[10] = -(displayVolume.Back() + displayVolume.Front()) / displayVolume.Depth;
            p.State[11] = -1.0f;
            p.State[14] = -2.0f * displayVolume.Front() * displayVolume.Back() / displayVolume.Depth;
            p.State[15] = 0.0f;

            p._position = Vector3(p.State[12], p.State[13], p.State[14]);
            p._size     = Vector3(p.State[0], p.State[5], p.State[10]);

            return p;
        }
        Transform Transform::PerspectiveProjection(float fov, float aspect, float znear, float zfar)
        {
            float hHeight = znear * tan(fov * Constants::Pi / 360.0);
            float hWidth = hHeight * aspect;

            Vector3 position(-hWidth, -hHeight, znear);
            Vector3 size(2.0f * hWidth, 2.0f * hHeight, zfar - znear);

            return PerspectiveProjection(Volume(position, size));
        }
        Transform Transform::Rotation(const Vector3& angles)
        {
            Transform r;
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
        Transform Transform::Rotation(float pitch, float yaw, float roll)
        {
            return Rotation(Vector3(pitch, yaw, roll));
        }
        Transform Transform::Scaling(const Vector3& size)
        {
            Transform s;
            s._size = size;

            s.State[0]  = size.X;
            s.State[5]  = size.Y;
            s.State[10] = size.Z;

            return s;
        }
        Transform Transform::Scaling(float x, float y, float z)
        {
            return Scaling(Vector3(x, y, z));
        }
        Transform Transform::Translation(const Vector3& position)
        {
            Transform t;
            t._position = position;

            t.State[12] = position.X;
            t.State[13] = position.Y;
            t.State[14] = position.Z;
            return t;
        }
        Transform Transform::Translation(float x, float y, float z)
        {
            return Translation(Vector3(x, y, z));
        }



        /** UTILITIES **/
        string Transform::Report() const
        {
            UpdateState();
            std::stringstream msg;
            msg << "Transformation Matrix Details:\n" << State.ToString();
            return msg.str();
        }



        /** OPERATORS **/
        Transform operator *(Transform left, Transform right)
        {
            int idxM, idxN, idxR = 0;
            float result[16];
            const float* leftState = left.ToArray();
            const float* rightState = right.ToArray();

            for (int a = 0; a < 16; a++)
            {
                idxM = a % 4;
                idxN = a / 4;
                idxR = idxN * 4;

                result[a] = 0;
                for (int b = 0; b < 4; b++)
                    result[a] += leftState[idxM + (b * 4)] * rightState[idxR + b];
            }

            return Transform(result);
        }

        bool Transform::operator ==(const Transform& other) const
        {
            if (this == (const Transform*) &other)
                return true;

            const float* leftState = ToArray();
            const float* rightState = other.ToArray();

            for (int a = 0; a < 16; a++)
                if (leftState[a] != rightState[a])
                    return false;

            return true;
        }



        /** PRIVATE UTILITIES **/
        /// <summary> Calculates the values of each element of the state matrix. </summary>
        /// <remarks>
        ///     This method effectively performs matrix multiplication to concatenate different affine transformations and does so in
        ///     a single pass, without actually generating and multiplying the component matrices. However, under that model, the
        ///     calculations performed here would correspond with multiplying transformation matrices in the following order:
        ///     
        ///         Translation * Roll * Yaw * Pitch * Scale
        ///     
        ///     The equations used in this method were derived using MATLAB.
        /// </remarks>
        void Transform::UpdateState() const
        {
            if (!_updateFlag) { return; }

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

            _updateFlag = false;
        }

    }
}