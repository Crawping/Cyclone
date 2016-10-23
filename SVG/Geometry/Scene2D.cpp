#include "Geometry/Scene2D.h"
#include "RenderStage2D.h"



namespace Cyclone
{
    namespace SVG
    {

        const List<IRenderStage*>& Scene2D::Stages() const
        {
            return Stages2D;
        }


        Scene2D::Scene2D()
        {
            Stages2D.Append( new RenderStage2D(&Buffers, &_settings) );
        }
        Scene2D::~Scene2D()
        {
            for (uint a = 0; a < Stages2D.Count(); a++)
                delete Stages2D(a);
        }


        void Scene2D::Add(const IRenderable2D<float>& entity)
        {
            Buffers.Add(entity);
        }
        void Scene2D::Remove(const IRenderable2D<float>& entity)
        {
            Buffers.Remove(entity);
        }

        void Scene2D::Update()
        {
            Buffers.Update();
        }

        void Scene2D::Update(const IRenderable2D<float>& entity)
        {
            Buffers.Update(entity);
        }

    }
}