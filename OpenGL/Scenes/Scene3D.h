/* CHANGELOG
 * Written by Josh Grooms on 20160724
 */

#pragma once
#include "Buffers/UniformData.h"
#include "GL/OpenGLAPI.h"
#include "Libraries/Material3D.h"
#include "Libraries/ResourceLibrary.h"
#include "Scenes/SceneLayer3D.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class IRenderStage;


        struct ResourceMapping
        {
            uint EntityID;
            uint GeometryID;
            uint IndicesCount;
            uint IndicesIndex;
            uint MaterialID;
            uint TransformID;
            uint VertexCount;
            uint VertexIndex;

            //RegistryKey<EntityData>     EntityKey;
            //RegistryKey<MaterialData>   MaterialKey;
            //PointTopologies             Topology;
            //RegistryKey<TransformData>  TransformKey;
        };



        /// <summary> A 3D scene representing a collection of renderable objects. </summary>
        class Scene3D :
            public SceneLayer3D,
            public virtual IScene
        {

            public:

                /** CONSTRUCTOR **/
                /// <summary> Constructs an empty scene object that can be populated with renderable entities. </summary>
                OpenGLAPI Scene3D(const string& name = "");
                OpenGLAPI ~Scene3D();

        };
    }
}
