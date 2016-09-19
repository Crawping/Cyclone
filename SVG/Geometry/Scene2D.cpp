#include "NVPR.h"
#include "Geometry/Scene2D.h"


namespace Cyclone
{
    namespace SVG
    {

        Scene2D::Scene2D()
        {

        }



        void Scene2D::Add(const Path2D& path)
        {
            Paths.insert(&path);
        }

        void Scene2D::Remove(const Path2D& path)
        {
            Paths.erase(&path);
        }

        void Scene2D::Render() const
        {
            glStencilFunc(GL_NOTEQUAL, 0, 0x1F);
            glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);

            for (const Path2D* p : Paths)
            {
                if (p->FillColor() != Color4::Transparent)
                {
                    nvStencilFillPath(p->ID(), p->FillMode(), 0x1F);
                    nvCoverFillPath(p->ID(), p->CoverMode());
                }

                if (p->StrokeColor() != Color4::Transparent)
                {
                    nvStencilStrokePath(p->ID(), 0x1, ~0);
                    nvCoverStrokePath(p->ID(), p->CoverMode());
                }
            }
        }

        void Scene2D::Update()
        {
            
        }

        void Scene2D::Update(const Path2D& path)
        {

        }

    }
}