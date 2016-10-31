/* CHANGELOG 
 * Written by Josh Grooms on 20161031
 */

#pragma once
#include "Interfaces/IRenderable.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {
        template<typename T> class GeometricEntity3D : 
            public IGeometric3D<T>
        {
            public:

                /** POSITIONAL PROPERTIES **/
                /// <summary> Gets the position of the entity along the world x-axis. </summary>
                virtual float X()                           const { return Position().X; }
		        /// <summary> Gets the position of the entity along the world y-axis. </summary>
                virtual float Y()                           const { return Position().Y; }
		        /// <summary> Gets the position of the entity along the world z-axis. </summary>
                virtual float Z()                           const { return Position().Z; }

		        /// <summary> Sets the position of the entity along the world x-axis. </summary>
                virtual GeometricEntity3D& X(float x)       { return Position(x, Y(), Z()); }
		        /// <summary> Sets the position of the entity along the world y-axis. </summary>
                virtual GeometricEntity3D& Y(float y)       { return Position(X(), y, Z()); }
		        /// <summary> Sets the position of the entity along the world z-axis. </summary>
                virtual GeometricEntity3D& Z(float z)       { return Position(X(), Y(), z); }

                /// <summary> Gets the position of the entity in 3D world coordinates. </summary>
                virtual const Vector3& Position()                                           const { return _world.Position(); }
		        /// <summary> Sets the position of the entity in 3D world coordinates. </summary>
                virtual GeometricEntity3D& Position(const Vector3& p)                       { _world.Position(p); return *this; }
		        /// <summary> Sets the position of the entity in 3D world coordinates. </summary>
                virtual GeometricEntity3D& Position(float x, float y, float z = 0.0f)       { return Position(Vector3(x, y, z)); }



                /** ROTATIONAL PROPERTIES **/
                /// <summary> Gets the angle of rotation about the x-axis in radians. </summary>
                virtual float Pitch()                                               const { return Orientation().X; }
                /// <summary> Gets the angle of rotation about the z-axis in radians. </summary>
                virtual float Roll()                                                const { return Orientation().Z; }
                /// <summary> Gets the angle of rotation about the y-axis in radians. </summary>
                virtual float Yaw()                                                 const { return Orientation().Y; }

                /// <summary> Sets the angle of rotation about the x-axis in radians. </summary>
                virtual GeometricEntity3D& Pitch(float p)                           { return Orientation(p, Yaw(), Roll()); }
                /// <summary> Sets the angle of rotation about the z-axis in radians. </summary>
                virtual GeometricEntity3D& Roll(float r)                            { return Orientation(Pitch(), Yaw(), r); }
                /// <summary> Sets the angle of rotation about the y-axis in radians. </summary>
                virtual GeometricEntity3D& Yaw(float y)                             { return Orientation(Pitch(), y, Roll()); }

                /// <summary> Gets the (x, y, z) rotation angles for the entity in 3D space. </summary>
                virtual const Vector3& Orientation()                                const { return _world.Orientation(); }
                /// <summary> Sets the (x, y, z) rotation angles for the entity in 3D space. </summary>
                virtual GeometricEntity3D& Orientation(const Vector3& value)        { _world.Orientation(value); return *this; }
                /// <summary> Sets the (x, y, z) rotation angles for the entity in 3D space. </summary>
                /// <param name="p"> The pitch, or rotation about the x-axis, in radians. </param>
                /// <param name="y"> The yaw, or rotation about the y-axis, in radians. </param>
                /// <param name="r"> The roll, or rotation about the z-axis, in radians. </param>
                virtual GeometricEntity3D& Orientation(float p, float y, float r)   { return Orientation(Vector3(p, y, r)); }



                /** SCALING PROPERTIES **/
		        /// <summary> Gets the size of the entity along the z-axis. </summary>
                virtual float Depth()                                               const { return Scale().Z; }
		        /// <summary> Gets the size of the entity along the y-axis. </summary>
                virtual float Height()                                              const { return Scale().Y; }
		        /// <summary> Gets the size of the entity along the x-axis. </summary>
                virtual float Width()                                               const { return Scale().X; }

		        /// <summary> Sets the size of the entity along the z-axis. </summary>
                virtual GeometricEntity3D& Depth(float z)                           { return Scale(Width(), Height(), z); }
		        /// <summary> Sets the size of the entity along the y-axis. </summary>
                virtual GeometricEntity3D& Height(float y)                          { return Scale(Width(), y, Depth()); }
		        /// <summary> Sets the size of the entity along the x-axis. </summary>
                virtual GeometricEntity3D& Width(float x)                           { return Scale(x, Height(), Depth()); }

                /// <summary> Gets the (x, y, z) scaling of the entity in 3D space. </summary>
                virtual const Vector3& Scale() const                                { return _world.Scale(); }
                /// <summary> Sets the (x, y, z) scaling of the entity in 3D space. </summary>
                virtual GeometricEntity3D& Scale(const Vector3& s)                  { _world.Scale(s); return *this; }
                /// <summary> Sets the (x, y, z) scaling of the entity in 3D space. </summary>
                virtual GeometricEntity3D& Scale(float x, float y, float z = 1.0f)  { return Scale(Vector3(x, y, z)); }


                virtual const Volume& Bounds()              const override { return _bounds; }
                virtual const Vector<uint>& Indices()       const override { return _indices; }
                virtual const ITransformation3D& World()    const override { return _worldTransform; }

                virtual ~IGeometric() { }

                virtual GeometricEntity& Rotate(const Vector3& value)           override 
                { 
                    _worldTransform.Rotate(value); 
                    return *this;
                }
                virtual GeometricEntity& Rotate(float x, float y, float z)      { return Rotate(Vector3(x, y, z)); }
                virtual GeometricEntity& Translate(const Vector3& value)        override
                {
                    _worldTransform.Translate(value);
                    return *this;
                }
                virtual GeometricEntity& Translate(float x, float y, float z)   { return Translate(Vector3(x, y, z)); }

            protected:
                
                GeometricEntity3D() { }


            private:

                Volume              _bounds;
                Vector<uint>        _indices;
                Transform           _modelTransform;
                Vector<T>           _points;
                VertexTopologies    _topology;
                Transform           _worldTransform;



        };
    }
}