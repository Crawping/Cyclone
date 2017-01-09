/* CHANGELOG
 * Written by Josh Grooms on 20161230
 */

#pragma once
#include "SVGAPI.h"
#include "Pipelines/RenderStage2D.h"
#include "Scenes/SceneComponent3D.h"



namespace Cyclone
{
    namespace { using namespace OpenGL; }

    namespace SVG
    {
        class SceneComponent2D : public SceneComponent
        {

            public:

                /** PROPERTIES **/
                SVGAPI List<IRenderStage&> Stages()             const override;



                /** CONSTRUCTOR **/
                SVGAPI SceneComponent2D(const string& name, ISceneLayer& parent);
                SVGAPI ~SceneComponent2D();



                /** UTILITIES **/
                SVGAPI bool Contains(const IRenderable& entity) const override;
                SVGAPI void Insert(const IRenderable& entity)   override;
                SVGAPI void Remove(const IRenderable& entity)   override;
                SVGAPI void Update()                            override;
                SVGAPI void Update(const IRenderable& entity)   override;

            private:

                struct ComponentData;

                bool            _needsUpdate;
                RenderStage2D   _stage;

                BST<const IRenderable2D*, ComponentData*> Resources;

        };
    }
}
