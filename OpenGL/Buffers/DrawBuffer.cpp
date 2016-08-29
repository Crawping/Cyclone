#include "Buffers/DrawBuffer.h"
#include "Interfaces/IRenderable.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** CONSTRUCTOR **/
        DrawBuffer::DrawBuffer() :
            _needsUpdate(false)
        {

        }



        /** BUFFER UTILITIES **/
        void DrawBuffer::Add(const IRenderableEntity& entity)
        {
            ExistingEntities.insert(&entity);
            _needsUpdate = true;
        }
        void DrawBuffer::Clear()
        {
            Commands.Clear();
            Entities.Clear();
            Vertices.Clear();
            _needsUpdate = true;
        }
        void DrawBuffer::Remove(const IRenderableEntity& entity)
        {
            ExistingEntities.erase(&entity);
            _needsUpdate = true;
        }



        /** BINDING UTILITIES **/
        void DrawBuffer::Bind(int slot) const
        {
            BindEntity(slot);
            BindResources();
        }
        void DrawBuffer::BindEntity(int slot) const
        {
            Commands.Bind(slot);
            Entities.Bind(slot);
            Vertices.Bind(slot);
        }
        void DrawBuffer::BindResources() const
        {

        }


        void DrawBuffer::Unbind() const
        {
            UnbindEntity();
            UnbindResources();
        }
        void DrawBuffer::UnbindEntity() const
        {
            Commands.Unbind();
            Entities.Unbind();
            Vertices.Unbind();
        }
        void DrawBuffer::UnbindResources() const
        {

        }


        void DrawBuffer::Update()
        {
            if (!NeedsUpdate()) { return; }

            Clear();

            for (auto* entity : ExistingEntities)
            {
                AddCommand(entity);
                AddEntity(entity);
                AddVertices(entity);
            }

            Commands.Update();
            Entities.Update();
            Vertices.Update();

            _needsUpdate = false;
        }



        void DrawBuffer::AddCommand(const IRenderableEntity* entity)
        {
            DrawCommand cmd =
            {
                entity->Vertices().Count(),
                1,
                Vertices.Count(),
                Commands.Count(),
            };
            Commands.Add(cmd);
        }
        void DrawBuffer::AddEntity(const IRenderableEntity* entity)
        {
            PerEntity data =
            {
                entity->World().ToArray(),
                entity->Color(),
            };
            Entities.Add(data);
        }
        void DrawBuffer::AddVertices(const IRenderableEntity* entity)
        {
            const Array<Vertex::Standard>& vertices = entity->Vertices();
            for (uint a = 0; a < vertices.Count(); a++)
                Vertices.Add(vertices(a));
        }

    }
}
