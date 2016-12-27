#include "Buffers/DrawBuffer2D.h"
#include "Interfaces/IMaterial.h"



namespace Cyclone
{
    namespace SVG
    {

        List<const IRenderable2D*> DrawBuffer2D::Entities() const
        {
            List<const IRenderable2D*> output;

            for (const auto& kvp : EntityIndices)
                output.Append(kvp.first);

            return output;
        }


        /** CONSTRUCTOR **/
        DrawBuffer2D::DrawBuffer2D() :
            _needsReallocation(false),
            _needsUpdate(false)
        {

        }


        /** BUFFER UTILITIES **/
        void DrawBuffer2D::Add(const IRenderable2D& entity)
        {
            if (EntityIndices.count(&entity)) { return; }

            EntityIndices[&entity] = ColorBuffer.Count();

            const auto& components = entity.Components();
            //for (uint a = 0; a < components.Count(); a++)
            //    Add(components(a));

            _needsReallocation = true;
            _needsUpdate = true;
        }
        void DrawBuffer2D::Clear()
        {
            ColorBuffer.Clear();
            EntityIndices.clear();
            ToUpdate.clear();

            _needsReallocation = true;
            _needsUpdate = true;
        }
        void DrawBuffer2D::Remove(const IRenderable2D& entity)
        {
            if (!EntityIndices.count(&entity)) { return; }

            EntityIndices.erase(&entity);
            _needsReallocation = true;
            _needsUpdate = true;
        }
        void DrawBuffer2D::Update()
        {
            if (!NeedsUpdate()) { return; }

            for (const auto& kvp : EntityIndices)
                kvp.first->Update();

            if (_needsReallocation)
            {
                ColorBuffer.Clear();
                for (const auto& kvp : EntityIndices)
                {
                    EntityIndices[kvp.first] = ColorBuffer.Count();
                    ColorBuffer.Add(kvp.first->Material().PrimaryColor());
                    ColorBuffer.Add(kvp.first->Material().SecondaryColor());
                }
            }
            else
            {
                for (const auto* entity : ToUpdate)
                {
                    uint idx = EntityIndices[entity];
                    ColorBuffer.Set(idx, entity->Material().PrimaryColor());
                    ColorBuffer.Set(idx + 1, entity->Material().SecondaryColor());
                }
            }

            ColorBuffer.Update();
            ToUpdate.clear();
            _needsReallocation = false;
            _needsUpdate = false;
        }
        void DrawBuffer2D::Update(const IRenderable2D& entity)
        {
            if (!EntityIndices.count(&entity)) { return; }

            //const auto& components = entity.Components();
            //for (uint a = 0; a < components.Count(); a++)
            //{
            //    if (EntityIndices.count(&entity))
            //        Update(components(a));
            //    else
            //        Add(components(a));
            //}

            ToUpdate.insert(&entity);
            _needsUpdate = true;
        }



        /** PRIVATE UTILITIES **/
        void DrawBuffer2D::Add(const IRenderable* entity)
        {
            if ( entity && (entity->Geometry().Topology() == VertexTopologies::Path) )
                Add( dynamic_cast<const IRenderable2D&>(*entity) );
        }
        void DrawBuffer2D::Update(const IRenderable* entity)
        {
            if ( entity && (entity->Geometry().Topology() == VertexTopologies::Path) )
            {
                const auto& entity2D = dynamic_cast<const IRenderable2D&>(*entity);
                if (EntityIndices.count(&entity2D))
                    Update(entity2D);
                else
                    Add(entity2D);
            }
        }

    }
}