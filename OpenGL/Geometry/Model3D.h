/* CHANGELOG
 * Written by Josh Grooms on 20160810
 */

#pragma once
#include "Collections/List.h"
#include "Geometry/Entity3D.h"
#include "Geometry/Vertex.h"



namespace Cyclone
{
    namespace OpenGL
    {


        class Model3D : public Entity3D
        {
            public:

                /** PROPERTIES **/
                virtual const Volume& Bounds()              const { return _geometry.Bounds(); }
                /// <summary> Gets the geometric data that define the shape of the mesh. </summary>
                virtual const Geometry3D& Geometry()        const override { return _geometry; }

                virtual bool IsEmpty()                      const { return _geometry.IsEmpty(); }

                /// <summary> Sets the geometric data that define the shape of the mesh. </summary>
                OpenGLAPI virtual Model3D& Geometry(const Geometry3D& value);



                /** CONSTRUCTORS **/
                /// <summary> Constructs a new empty 3D mesh for rendering models in scenes. </summary>
                OpenGLAPI Model3D();
                /// <summary> Constructs a new 3D mesh that is initialized with pre-defined geometric data. </summary>
                /// <param name="geometry"> An existing 3D geometry data object. </param>
                OpenGLAPI Model3D(const Geometry3D& geometry);

            protected:
            
                /** DATA **/
                Geometry3D  _geometry;

        };
    }
}
