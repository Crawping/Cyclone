/* CHANGELOG
 * Written by Josh Grooms on 20150929
 */

#pragma once
#include "EnumerationsGL.h"
#include "Geometry/Geometry3D.h"
#include "Geometry/Transform3D.h"
#include "GL/OpenGLAPI.h"
#include "Imaging/Color4.h"
#include "Interfaces/IRenderable.h"
#include "Libraries/Material3D.h"
#include "Spatial/Volume.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class Texture3D;
    
        class Entity3D : 
            public virtual IRenderable
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
                virtual Entity3D& X(float x)                { return Position(x, Y(), Z()); }
		        /// <summary> Sets the position of the entity along the world y-axis. </summary>
                virtual Entity3D& Y(float y)                { return Position(X(), y, Z()); }
		        /// <summary> Sets the position of the entity along the world z-axis. </summary>
                virtual Entity3D& Z(float z)                { return Position(X(), Y(), z); }



                /** ROTATIONAL PROPERTIES **/
                /// <summary> Gets the angle of rotation about the x-axis in radians. </summary>
                virtual float Pitch()                       const { return Orientation().X; }
                /// <summary> Gets the angle of rotation about the z-axis in radians. </summary>
                virtual float Roll()                        const { return Orientation().Z; }
                /// <summary> Gets the angle of rotation about the y-axis in radians. </summary>
                virtual float Yaw()                         const { return Orientation().Y; }

                /// <summary> Sets the angle of rotation about the x-axis in radians. </summary>
                virtual Entity3D& Pitch(float p)            { return Orientation(p, Yaw(), Roll()); }
                /// <summary> Sets the angle of rotation about the z-axis in radians. </summary>
                virtual Entity3D& Roll(float r)             { return Orientation(Pitch(), Yaw(), r); }
                /// <summary> Sets the angle of rotation about the y-axis in radians. </summary>
                virtual Entity3D& Yaw(float y)              { return Orientation(Pitch(), y, Roll()); }



                /** SCALING PROPERTIES **/
		        /// <summary> Gets the size of the entity along the z-axis. </summary>
                virtual float Depth()                       const { return Scale().Z; }
		        /// <summary> Gets the size of the entity along the y-axis. </summary>
                virtual float Height()                      const { return Scale().Y; }
		        /// <summary> Gets the size of the entity along the x-axis. </summary>
                virtual float Width()                       const { return Scale().X; }

		        /// <summary> Sets the size of the entity along the z-axis. </summary>
                virtual Entity3D& Depth(float z)            { return Scale(Width(), Height(), z); }
		        /// <summary> Sets the size of the entity along the y-axis. </summary>
                virtual Entity3D& Height(float y)           { return Scale(Width(), y, Depth()); }
		        /// <summary> Sets the size of the entity along the x-axis. </summary>
                virtual Entity3D& Width(float x)            { return Scale(x, Height(), Depth()); }


                
                /** BATCH SPATIAL PROPERTIES **/
                /// <summary> Gets the (x, y, z) position of the entity in model space. </summary>
                virtual const Vector3& Offset()             const { return _transforms.Offset(); }
                /// <summary> Gets the (x, y, z) rotation angles for the entity in world space. </summary>
                virtual const Vector3& Orientation()        const { return _transforms.Orientation(); }
                /// <summary> Gets the (x, y, z) position of the entity in world space. </summary>
                virtual const Vector3& Position()           const { return _transforms.Position(); }
                /// <summary> Gets the (x, y, z) scaling of the entity in world space. </summary>
                virtual const Vector3& Scale()              const { return _transforms.Scale(); }
                /// <summary> Gets the (x, y, z) scaling of the entity in model space. </summary>
                virtual const Vector3& Size()               const { return _transforms.Scale(); }
		        
                /// <summary> Sets the (x, y, z) position of the entity in model space. </summary>
                virtual Entity3D& Offset(const Vector3& value)
                {
                    _transforms.Offset(value);
                    return *this;
                }
                /// <summary> Sets the (x, y, z) position of the entity in model space. </summary>
                virtual Entity3D& Offset(float x, float y, float z)             { return Offset(Vector3(x, y, z)); }
                /// <summary> Sets the (x, y, z) rotation of for the entity in world space. </summary>
                virtual Entity3D& Orientation(const Vector3& value)
                {
                    _transforms.Orientation(value);
                    return *this;
                }
                /// <summary> Sets the (x, y, z) rotation angles of the entity in world space. </summary>
                /// <param name="p"> The pitch, or rotation about the x-axis, in radians. </param>
                /// <param name="y"> The yaw, or rotation about the y-axis, in radians. </param>
                /// <param name="r"> The roll, or rotation about the z-axis, in radians. </param>
                virtual Entity3D& Orientation(float p, float y, float r)        { return Orientation(Vector3(p, y, r)); }
                /// <summary> Sets the (x, y, z) position of the entity in world space. </summary>
                virtual Entity3D& Position(const Vector3& p)
                {
                    _transforms.Position(p);
                    return *this;
                }
                /// <summary> Sets the (x, y, z) position of the entity in world space. </summary>
                virtual Entity3D& Position(float x, float y, float z = 0.0f)    { return Position(Vector3(x, y, z)); }
                /// <summary> Sets the (x, y, z) scaling of the entity in world space. </summary>
                virtual Entity3D& Scale(const Vector3& s)
                {
                    _transforms.Scale(s);
                    return *this;
                }
                /// <summary> Sets the (x, y, z) scaling of the entity in world space. </summary>
                virtual Entity3D& Scale(float x, float y, float z = 1.0f)       { return Scale(Vector3(x, y, z)); }
                /// <summary> Sets the (x, y, z) scaling of the entity in model space. </summary>
                virtual Entity3D& Size(const Vector3& value)
                {
                    _transforms.Size(value);
                    return *this;
                }
                /// <summary> Sets the (x, y, z) scaling of the entity in model space. </summary>
                virtual Entity3D& Size(float x, float y, float z)
                {
                    return Size(Vector3(x, y, z));
                }
                


                /** MATERIAL PROPERTIES **/
                /// <summary> Gets a reference to the primary color of the entity. </summary>
                virtual const Color4& PrimaryColor()                    const { return _material.PrimaryColor(); }
                /// <summary> Gets a reference to the secondary color of the entity. </summary>
                virtual const Color4& SecondaryColor()                  const { return _material.SecondaryColor(); }
                /// <summary> Gets a pointer to the texture associated with an entity. </summary>
		        virtual const Texture3D* Texture()                      const { return _material.Texture(); }

                /// <summary> Sets the primary color of the entity. </summary>
                virtual Entity3D& PrimaryColor(const Color4& value)
                { 
                    _material.PrimaryColor(value);
                    return *this;
                }
                /// <summary> Sets the secondary color of the entity. </summary>
                virtual Entity3D& SecondaryColor(const Color4& value)
                {
                    _material.SecondaryColor(value);
                    return *this;
                }
                /// <summary> Sets the texture to be used when rendering the entity (NOT YET IMPLEMENTED). </summary>
                virtual Entity3D& Texture(const Texture3D* value)
                {
                    _material.Texture(value);
                    return *this;
                }


                
                /** RENDERABLE INTERFACE PROPERTIES **/
                /// <summary> Gets a list of other renderable components that comprise or are associated with the entity. </summary>
                virtual List<const IRenderable&> Components()           const override { return List<const IRenderable&>(); }
                /// <summary> Gets whether the entity is visible in the rendered environment. </summary>
                virtual bool IsVisible()                                const override { return _isVisible; }
                /// <summary> Gets the material used to style the entity in the rendered environment. </summary>
                virtual const Material3D& Material()                    const override { return _material; }
                /// <summary> Gets the spatial transformations used to place the entity in the rendered environment. </summary>
                virtual const Transform3D& Transforms()                 const override { return _transforms; }

                /// <summary> Sets whether the entity is visible in a rendered environment. </summary>
                virtual Entity3D& IsVisible(bool value)
                {
                    _isVisible = value;
                    return *this;
                }
                /// <summary> Sets the material used to style the entity in the rendered environment. </summary>
                virtual Entity3D& Material(const Material3D& value)
                { 
                    _material = value;
                    return *this;
                }
                /// <summary> Sets the spatial transformations used to place the entity in the rendered environment. </summary>
                virtual Entity3D& Transforms(const Transform3D& value)
                {
                    _transforms = value;
                    return *this;
                }



                /** DESTRUCTOR **/
                /// <summary> Destroys any special resources held by this entity. </summary>
                /// <remarks> The destructor for this base class actually performs no actions whatsoever. </remarks>
                virtual ~Entity3D() { }



                /** UTILITIES **/
                /// <summary> Sets the (x, y, z) rotation angles for the entity relative to their current values. </summary>
                virtual Entity3D& Rotate(const Vector3& value)           //override
                {
                    _transforms.Rotate(value);
                    return *this;
                }
                /// <summary> Sets the (x, y, z) rotation angles for the entity relative to their current values. </summary>
                virtual Entity3D& Rotate(float x, float y, float z) { return Rotate(Vector3(x, y, z)); }
                /// <summary> Sets the position of the entity in 3D space relative to its current position. </summary>
                virtual Entity3D& Translate(const Vector3& value)        //override
                {
                    _transforms.Translate(value);
                    return *this;
                }
                /// <summary> Sets the position of the entity in 3D space relative to its current position. </summary>
                virtual Entity3D& Translate(float x, float y, float z) { return Translate(Vector3(x, y, z)); }

            protected:

                /** PROPERTIES **/
                virtual Material3D& Material()      { return _material; }
                virtual Transform3D& Transforms()   { return _transforms; }



                /** CONSTRUCTOR **/
                Entity3D() : 
                    _isVisible(true)
                {
                    
                }

            private:
                
                /** PROPERTY DATA **/
                bool            _isVisible;
                Material3D      _material;
                Transform3D     _transforms;

        };
    }
}
