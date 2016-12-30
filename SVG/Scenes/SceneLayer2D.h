/* CHANGELOG
 * Written by Josh Grooms on 20161230
 */

#pragma once
#include "SVGAPI.h"
#include "Scenes/SceneLayer3D.h"



namespace Cyclone
{
    namespace { using namespace OpenGL; }

    namespace SVG
    {
        class SceneLayer2D : public SceneLayer3D
        {

            public:

                /** PROPERTIES **/
                SVGAPI List<BufferBinding> Buffers()        const override;
                SVGAPI List<ISceneComponent&> Components()  const override;
                SVGAPI List<IRenderStage&> Stages()         const override;



                /** CONSTRUCTOR **/
                SVGAPI SceneLayer2D(const string& name, ISceneLayer& parent);



                /** UTILITIES **/
                SVGAPI void Insert(const IRenderable& entity)                       override;
                SVGAPI void Insert(const string& name, ISceneComponent& stage)      override;
                SVGAPI void Remove(const string& name)                              override;
                SVGAPI void Update()                                                override;
                SVGAPI void Update(const IRenderable& entity)                       override;

            protected:

                SVGAPI ResourceMapping& Register(const IRenderable& entity)         override;

            private:
                

        };
    }
}
