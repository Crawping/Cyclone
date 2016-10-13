#include "Geometry/SceneSVG.h"
#include "RenderStage2D.h"
//#include "Interfaces/IRenderStage.h"



namespace Cyclone
{
    namespace SVG
    {

        List<IRenderStage*> SceneSVG::Stages() const
        {
            return Stages2D;
        }


        SceneSVG::SceneSVG()
        {
            
        }
        SceneSVG::~SceneSVG()
        {
            for (uint a = 0; a < Stages2D.Count(); a++)
                delete Stages2D(a);
        }


        void SceneSVG::Add(const IRenderable2D<float>& entity)
        {
            if (Entities.count(&entity)) { return; }
            
            Entities.insert(&entity);
            Colors.Add(entity.PrimaryColor());
            Colors.Add(entity.SecondaryColor());

            //const auto& components = entity.Components();
            //for (uint a = 0; a < components.Count(); a++)
            //    if (components(a)->Topology() == VertexTopologies::Path)
            //        Add( dynamic_cast<IRenderable2D<float>&>(*components(a)) );

        }
        void SceneSVG::Remove(const IRenderable2D<float>& entity)
        {
            Entities.erase(&entity);
        }

        void SceneSVG::Update()
        {
            for (uint a = 0; a < Stages2D.Count(); a++)
                delete Stages2D(a);

            Stages2D.Clear();

            for (const auto* e : Entities)
                e->Update();

            Colors.Update();
            Stages2D.Append( new RenderStage2D(&Colors, &Entities, &_settings) );
        }

    }
}