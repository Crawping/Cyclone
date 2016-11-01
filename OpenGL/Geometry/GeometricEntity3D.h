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
            public virtual IGeometric3D<T>
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


                virtual const Vector3& Offset() const 
                { 
                    return _modelTransform.Position();
                }

                virtual GeometricEntity3D& Offset(const Vector3& value)
                { 
                    _modelTransform.Position(value);
                    return *this;
                }

                virtual GeometricEntity3D& Offset(float x, float y, float z)                { return Offset(Vector3(x, y, z)); }
                /// <summary> Gets the position of the entity in 3D world coordinates. </summary>
                virtual const Vector3& Position()                                           const { return _worldTransform.Position(); }
		        /// <summary> Sets the position of the entity in 3D world coordinates. </summary>
                virtual GeometricEntity3D& Position(const Vector3& p)                       { _worldTransform.Position(p); return *this; }
		        /// <summary> Sets the position of the entity in 3D world coordinates. </summary>
                virtual GeometricEntity3D& Position(float x, float y, float z = 0.0f)       { return Position(Vector3(x, y, z)); }



                /** ROTATIONAL PROPERTIES **/
                /// <summary> Gets the angle of rotation about the x-axis in radians. </summary>
                virtual float Pitch()                       const { return Orientation().X; }
                /// <summary> Gets the angle of rotation about the z-axis in radians. </summary>
                virtual float Roll()                        const { return Orientation().Z; }
                /// <summary> Gets the angle of rotation about the y-axis in radians. </summary>
                virtual float Yaw()                         const { return Orientation().Y; }

                /// <summary> Sets the angle of rotation about the x-axis in radians. </summary>
                virtual GeometricEntity3D& Pitch(float p)   { return Orientation(p, Yaw(), Roll()); }
                /// <summary> Sets the angle of rotation about the z-axis in radians. </summary>
                virtual GeometricEntity3D& Roll(float r)    { return Orientation(Pitch(), Yaw(), r); }
                /// <summary> Sets the angle of rotation about the y-axis in radians. </summary>
                virtual GeometricEntity3D& Yaw(float y)     { return Orientation(Pitch(), y, Roll()); }

                /// <summary> Gets the (x, y, z) rotation angles for the entity in 3D space. </summary>
                virtual const Vector3& Orientation()                                const { return _worldTransform.Orientation(); }
                /// <summary> Sets the (x, y, z) rotation angles for the entity in 3D space. </summary>
                virtual GeometricEntity3D& Orientation(const Vector3& value)        { _worldTransform.Orientation(value); return *this; }
                /// <summary> Sets the (x, y, z) rotation angles for the entity in 3D space. </summary>
                /// <param name="p"> The pitch, or rotation about the x-axis, in radians. </param>
                /// <param name="y"> The yaw, or rotation about the y-axis, in radians. </param>
                /// <param name="r"> The roll, or rotation about the z-axis, in radians. </param>
                virtual GeometricEntity3D& Orientation(float p, float y, float r)   { return Orientation(Vector3(p, y, r)); }



                /** SCALING PROPERTIES **/
		        /// <summary> Gets the size of the entity along the z-axis. </summary>
                virtual float Depth()                       const { return Scale().Z; }
		        /// <summary> Gets the size of the entity along the y-axis. </summary>
                virtual float Height()                      const { return Scale().Y; }
		        /// <summary> Gets the size of the entity along the x-axis. </summary>
                virtual float Width()                       const { return Scale().X; }

		        /// <summary> Sets the size of the entity along the z-axis. </summary>
                virtual GeometricEntity3D& Depth(float z)   { return Scale(Width(), Height(), z); }
		        /// <summary> Sets the size of the entity along the y-axis. </summary>
                virtual GeometricEntity3D& Height(float y)  { return Scale(Width(), y, Depth()); }
		        /// <summary> Sets the size of the entity along the x-axis. </summary>
                virtual GeometricEntity3D& Width(float x)   { return Scale(x, Height(), Depth()); }

                /// <summary> Gets the (x, y, z) scaling of the entity in 3D space. </summary>
                virtual const Vector3& Scale() const
                { 
                    return _worldTransform.Scale();
                }
                /// <summary> Sets the (x, y, z) scaling of the entity in 3D space. </summary>
                virtual GeometricEntity3D& Scale(const Vector3& s)
                { 
                    _worldTransform.Scale(s);
                    return *this;
                }
                /// <summary> Sets the (x, y, z) scaling of the entity in 3D space. </summary>
                virtual GeometricEntity3D& Scale(float x, float y, float z = 1.0f)
                { 
                    return Scale(Vector3(x, y, z)); 
                }

                virtual const Vector3& Size() const
                { 
                    return _modelTransform.Scale();
                }

                virtual GeometricEntity3D& Size(const Vector3& value)
                {
                    _modelTransform.Scale(value); 
                    return *this; 
                }

                virtual GeometricEntity3D& Size(float x, float y, float z)
                { 
                    return Size(Vector3(x, y, z));
                }



                /** GEOMETRIC PROPERTIES **/
                virtual const Volume& Bounds()                      const override { return _bounds; }
                /// <summary> Gets a reference to the array of indices that specify the vertex rendering order. </summary>
                virtual const Vector<uint>& Indices()               const override { return _indices; }
                virtual const ITransformation3D& ModelTransform()   const override { return _modelTransform; }
                /// <summary> Gets a reference to the array of points that define the shape of an entity in 3D model space. </summary>
                virtual const Vector<T>& Points()                   const override { return _points; }
                /// <summary> Gets the type of primitive that the points in the vertex array construct. </summary>
                virtual VertexTopologies Topology()                 const override { return _topology; }
                /// <summary> Gets a reference to the world transformation matrix of an entity. </summary>
                /// <remarks>
                ///     The world transform defines the position, scale, and orientation of an entity in 3D space. It is typically 
                ///     used to apply the rotation, scaling, and translation operations that place the geometry of an entity 
                ///     (defined by the <see cref="Points"/> method) into its correct position in a three-dimensional environment 
                ///     called 'world' space.
                /// </remarks>
                virtual const ITransformation3D& WorldTransform()   const override { return _worldTransform; }



                /** DESTRUCTOR **/
                virtual ~GeometricEntity3D() { }



                /** UTILITIES **/
                /// <summary> Sets the (x, y, z) rotation angles for the entity relative to their current values. </summary>
                virtual GeometricEntity3D& Rotate(const Vector3& value)           override 
                { 
                    _worldTransform.Rotate(value); 
                    return *this;
                }
                /// <summary> Sets the (x, y, z) rotation angles for the entity relative to their current values. </summary>
                virtual GeometricEntity3D& Rotate(float x, float y, float z)      { return Rotate(Vector3(x, y, z)); }
                /// <summary> Sets the position of the entity in 3D space relative to its current position. </summary>
                virtual GeometricEntity3D& Translate(const Vector3& value)        override
                {
                    _worldTransform.Translate(value);
                    return *this;
                }
                /// <summary> Sets the position of the entity in 3D space relative to its current position. </summary>
                virtual GeometricEntity3D& Translate(float x, float y, float z)   { return Translate(Vector3(x, y, z)); }

            protected:
                
                /** PROPERTIES **/
                virtual GeometricEntity3D& Bounds(const Volume& value) { _bounds = value; return *this; }


                /** CONSTRUCTOR **/
                GeometricEntity3D(VertexTopologies topology, const Vector<T>& points, const Vector<uint>& indices) :
                    _indices(indices),
                    _points(points),
                    _topology(topology)
                { 
                
                }


            private:

                /** PROPERTY DATA **/
                Volume              _bounds;
                Vector<uint>        _indices;
                Transform           _modelTransform;
                Vector<T>           _points;
                VertexTopologies    _topology;
                Transform           _worldTransform;



        };
    }
}
