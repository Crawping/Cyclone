/* CHANGELOG
 * Written by Josh Grooms on 20161011
 */

#pragma once
#include "SVGAPI.h"
#include "Collections/Set.h"
#include "Imaging/Color4.h"
#include "Interfaces/IRenderable2D.h"
#include "Pipelines/RenderStage.h"


namespace Cyclone
{
    namespace { using namespace OpenGL; }

    namespace SVG
    {

        struct RenderStage2D : public RenderStage
        {

            public:
                
                /** CONSTRUCTOR **/
                SVGAPI RenderStage2D();



                /** UTILITIES **/
                SVGAPI void ClearEntities();
                SVGAPI void Insert(const IRenderable2D& entity);
                SVGAPI void Remove(const IRenderable2D& entity);
                SVGAPI void Render()                        const override;
                SVGAPI void Update();

            protected:
                
                /** UTILITIES **/
                SVGAPI int GetResourceID(const string& name)            const;
                SVGAPI int GetUniformID(const string& name)             const;
                SVGAPI void SetResource(int id, const Color4& value)    const;
                SVGAPI void SetUniform(int id, const Color4& value)     const;
                SVGAPI void SetUniform(int id, int value)               const;


            private:
                
                Set<const IRenderable2D*> Entities;

        };
    }
}
