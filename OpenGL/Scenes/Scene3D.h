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
            uint IndicesCount;
            uint IndicesIndex;
            uint TransformIndex;
            uint VertexCount;
            uint VertexIndex;

            RegistryKey<EntityData>     EntityKey;
            RegistryKey<MaterialData>   MaterialKey;
            VertexTopologies            Topology;
        };



        /// <summary> A 3D scene representing a collection of renderable objects. </summary>
        class Scene3D :
            public SceneLayer3D,
            public virtual IScene
        {

            public:
                
                bool NeedsUpdate()                              const override { return true; }



                /** CONSTRUCTOR **/
                /// <summary> Constructs an empty scene object that can be populated with renderable entities. </summary>
                OpenGLAPI Scene3D(const string& name = "");
                OpenGLAPI ~Scene3D();

        };
    }
}
