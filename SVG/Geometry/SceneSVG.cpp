#include "Geometry/SceneSVG.h"



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

        }


        void SceneSVG::Add(const IRenderable2D<float>& entity)
        {
            if (Entities.count(&entity)) { return; }
            
            Entities.insert(&entity);
            FillColors.Add(entity.PrimaryColor());
            StrokeColors.Add(entity.SecondaryColor());

            const auto& components = entity.Components();
            for (uint a = 0; a < components.Count(); a++)
                if (components(a)->Topology() == VertexTopologies::Path)
                    Add( dynamic_cast<IRenderable2D<float>&>(*components(a)) );


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

            
        }

    }
}