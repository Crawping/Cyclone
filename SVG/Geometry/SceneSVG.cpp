#include "Geometry/SceneSVG.h"
#include "RenderStage2D.h"
//#include "Interfaces/IRenderStage.h"



namespace Cyclone
{
    namespace SVG
    {

        const List<IRenderStage*>& SceneSVG::Stages() const
        {
            return Stages2D;
        }


        SceneSVG::SceneSVG()
        {
            Stages2D.Append( new RenderStage2D(&Buffers, &_settings) );
        }
        SceneSVG::~SceneSVG()
        {
            for (uint a = 0; a < Stages2D.Count(); a++)
                delete Stages2D(a);
        }


        void SceneSVG::Add(const IRenderable2D<float>& entity)
        {
            Buffers.Add(entity);

            //if (Entities.count(&entity)) { return; }
            
            //Entities.insert(&entity);
            //Colors.Add(entity.PrimaryColor());
            //Colors.Add(entity.SecondaryColor());

            //const auto& components = entity.Components();
            //for (uint a = 0; a < components.Count(); a++)
            //    if (components(a)->Topology() == VertexTopologies::Path)
            //        Add( dynamic_cast<IRenderable2D<float>&>(*components(a)) );

        }
        void SceneSVG::Remove(const IRenderable2D<float>& entity)
        {
            Buffers.Remove(entity);
            //Entities.erase(&entity);
        }

        void SceneSVG::Update()
        {
            Buffers.Update();

            //for (const auto* e : Entities)
            //{
            //    const auto& components = e->Components();
            //    for (uint a = 0; a < components.Count(); a++)
            //        if (components(a)->Topology() == VertexTopologies::Path)
            //            Add(dynamic_cast<IRenderable2D<float>&>(*components(a)));
            //}
            //
            //for (const auto* e : Entities)
            //    e->Update();

            //Colors.Update();
        }

        void SceneSVG::Update(const IRenderable2D<float>& entity)
        {
            Buffers.Update(entity);
        }

    }
}