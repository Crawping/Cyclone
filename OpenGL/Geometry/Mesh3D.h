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


        class Mesh3D : public Entity3D
        {
            public:

                /** PROPERTIES **/
                const Geometry3D& Geometry()        const override { return _geometry; }

                OpenGLAPI virtual Mesh3D& Geometry(const Geometry3D& value);



                /** CONSTRUCTORS **/
                OpenGLAPI Mesh3D();
                OpenGLAPI Mesh3D(const Geometry3D& geometry);

            protected:
            
                virtual Geometry3D& Geometry()      { return _geometry; }



                /** UTILITIES **/
                OpenGLAPI void Append(const Vertex& vertices);
                OpenGLAPI void Append(const ICollection<Vertex>& vertices);


            private:
                
                Geometry3D  _geometry;
        };
    }
}
