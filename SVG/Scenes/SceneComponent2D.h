/* CHANGELOG
 * Written by Josh Grooms on 20161230
 */

#pragma once
#include "SVGAPI.h"
#include "Scenes/SceneComponent3D.h"


namespace Cyclone
{
    namespace { using namespace OpenGL; }

    namespace SVG
    {
        class SceneComponent2D : public SceneComponent3D
        {

            public:
                
                /** PROPERTIES **/
                SVGAPI List<IRenderStage&> Stages()             const override;



                /** CONSTRUCTOR **/
                SVGAPI SceneComponent2D(const string& name, ISceneLayer& parent);


                /** UTILITIES **/
                SVGAPI void Insert(const IRenderable& entity)   override;
                SVGAPI void Update()                            override;

            private:

                Set<const ResourceMapping*>     Resources;


        };
    }
}
