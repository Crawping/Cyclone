/* CHANGELOG
 * Written by Josh Grooms on 20160902
 */

#pragma once
#include "Buffers/CommandBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/UniformData.h"
#include "Buffers/VertexBuffer.h"
#include "Interfaces/IGraphicsBuffer.h"
#include "Interfaces/IRenderable.h"
#include "Spatial/Transform.h"
#include <set>

#include "Utilities.h"

namespace Cyclone
{
    namespace OpenGL
    {

        template<typename T = Vertex::Standard>
        class IndexedDrawBuffer : public IGraphicsBuffer
        {
            public:

                /** PROPERTIES **/
                /// <summary> Gets the number of drawing commands currently stored in this buffer. </summary>
                uint Count()                    const override { return Commands.Count(); }
                /// <summary> A method implemented for <see cref="IBindable"/> compatibility that has no purpose here. </summary>
                /// <returns> This method always returns zero. </returns>
                /// <remarks>
                ///     Instances of this class are a collection of buffer objects that do not have one single identifier. Thus,
                ///     while this property is necessary for inheritting from <see cref="IBindable"/>, it performs no actions and
                ///     should never be used.
                /// </remarks>
                uint ID()                       const override { return 0; }
                /// <summary> Gets whether this buffer has data updates queued for transfer to the GPU. </summary>
                bool NeedsUpdate()              const override { return _needsUpdate; }



                /** CONSTRUCTOR **/
                IndexedDrawBuffer() : _needsUpdate(false) { }



                /** BUFFER UTILITIES **/
                void Add(const IRenderableEntity& entity)
                {
                    ExistingEntities.insert(&entity);
                    _needsUpdate = true;
                }
                void Clear()                    override
                {
                    Commands.Clear();
                    Entities.Clear();
                    Indices.Clear();
                    Vertices.Clear();
                    _needsUpdate = true;
                }
                void Remove(const IRenderableEntity& entity)
                {
                    ExistingEntities.erase(&entity);
                    _needsUpdate = true;
                }
                void Update()                   override
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
                    Indices.Update();
                    Vertices.Update();

                    _needsUpdate = false;
                }



                /** BINDING UTILITIES **/
                void Bind(int slot = 0)         const override
                {
                    BindEntity(slot);
                    BindResources();
                }
                void BindEntity(int slot = 0)   const override
                {
                    Commands.Bind(slot);
                    Entities.Bind(slot);
                    Vertices.Bind(slot);
                    Indices.Bind(slot);
                }
                void BindResources()            const override { }

                void Unbind()                   const override
                {
                    UnbindEntity();
                    UnbindResources();
                }
                void UnbindEntity()             const override
                {
                    Indices.Unbind();
                    Vertices.Unbind();
                    Entities.Unbind();
                    Commands.Unbind();
                }
                void UnbindResources()          const override { }



            private:

                /** PROPERTY DATA **/
                bool                                _needsUpdate;



                /** DATA COLLECTIONS **/
                /// <summary> A collection of indirect drawing commands used to render geometry on the GPU. </summary>
                IndexedCommandBuffer                Commands;
                /// <summary> A collection of uniform data that describes the appearance of rendered geometry on the GPU. </summary>
                UniformBuffer<PerEntity>            Entities;

                IndexBuffer                         Indices;
                /// <summary> A collection of vertices used to build geometry on the GPU. </summary>
                VertexBuffer<T>                     Vertices;

                std::set<const IRenderableEntity*>  ExistingEntities;



                /** UTILITIES **/
                void AddCommand(const IRenderableEntity* entity)
                {
                    IndexedDrawCommand cmd =
                    {
                        entity->Indices().Count(),
                        1,
                        Indices.Count(),
                        Vertices.Count(),
                        Commands.Count(),
                    };
                    Commands.Add(cmd);
                }
                void AddEntity(const IRenderableEntity* entity)
                {
                    PerEntity data =
                    {
                        entity->World().ToArray(),
                        entity->Color(),
                    };
                    Entities.Add(data);
                }
                void AddVertices(const IRenderableEntity* entity)
                {
                    const Array<Vertex::Standard>& vertices = entity->Vertices();
                    for (uint a = 0; a < vertices.Count(); a++)
                        Vertices.Add(vertices(a));

                    const Array<uint>& indices = entity->Indices();
                    for (uint a = 0; a < indices.Count(); a++)
                        Indices.Add(indices(a));
                }

        };
    }
}