/* CHANGELOG
 * Written by Josh Grooms on 20160821
 */

#pragma once
#include "Buffers/CommandBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/UniformData.h"
#include "Buffers/VertexBuffer.h"
#include "Interfaces/ICollection.h"
#include "Interfaces/IGraphicsBuffer.h"
#include "Interfaces/IRenderable.h"
#include <map>
#include <set>



namespace Cyclone
{
    namespace OpenGL
    {

        /// <summary> A class that holds and manages a collection of buffers related to drawing a single type of primitive geometry. </summary>
        /// <typeparam name="T"> The type name of the command data structure used by the buffer. </typeparam>
        /// <typeparam name="U"> The type name of the per-entity data structure used by the buffer. </typeparam>
        /// <typeparam name="V"> The type name of the vertex data structure used by the buffer. </typeparam>
        template<typename T, typename U = PerEntity, typename V = Vertex::Standard>
        class DrawBuffer3D : public IGraphicsBuffer
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
                bool NeedsUpdate()              const override { return _needsUpdate || _needsReallocation; }



                /** CONSTRUCTOR **/
                /// <summary> Constructs an empty new drawing buffer for use in rendering geometry on the GPU. </summary>
                DrawBuffer3D() :
                    _needsReallocation(false),
                    _needsUpdate(false)
                {

                }



                /** BUFFER UTILITIES **/
                /// <summary> Adds a 3D renderable entity to the drawing buffer. </summary>
                /// <param name="entity"> A reference to the 3D renderable entity to be added to the drawing buffer. </param>
                /// <remarks> If the inputted entity is already present, then this method has no effect on the buffer. </remarks>
                void Add(const IRenderable3D<V>& entity)
                {
                    if (EntityIndices.count(&entity)) { return; }

                    const auto& components = entity.Components();
                    for (uint a = 0; a < components.Count(); a++)
                        Add(*components(a));

                    EntityIndices[&entity] = Commands.Count();
                    _needsReallocation = true;
                    _needsUpdate = true;
                }
                /// <summary> Clears the contents of the drawing buffer. </summary>
                void Clear()                                    override
                {
                    ClearBuffers();
                    EntityIndices.clear();
                    ToUpdate.clear();
                }
                /// <summary> Determines whether the drawing buffer contains a particular 3D renderable entity. </summary>
                /// <returns> A Boolean <c>true</c> if the entity is present in the buffer, or <c>false</c> otherwise. </returns>
                bool Contains(const IRenderable3D<V>& entity)   const { return EntityIndices.count(&entity); }
                /// <summary> Removes a 3D renderable entity from the drawing buffer. </summary>
                /// <param name="entity"> A reference to the 3D renderable entity to be removed from the drawing buffer. </param>
                /// <remarks> If the inputted entity isn't already present, then this method had no effect on the buffer. </remarks>
                void Remove(const IRenderable3D<V>& entity)
                {
                    if (!EntityIndices.count(&entity)) { return; }

                    EntityIndices.erase(&entity);
                    _needsReallocation = true;
                    _needsUpdate = true;
                }
                void Update()                                   override
                {
                    if (!NeedsUpdate()) { return; }

                    if (_needsReallocation)
                    {
                        ClearBuffers();
                        for (const auto& kvp : EntityIndices)
                        {
                            EntityIndices[kvp.first] = Commands.Count();

                            AddCommand(kvp.first);
                            AddEntity(kvp.first);
                            AddVertices(kvp.first);
                        }

                        Commands.Update();
                        Entities.Update();
                        Vertices.Update();
                        Indices.Update();
                    }
                    else
                    {
                        for (const auto* entity : ToUpdate)
                        {
                            uint idx = EntityIndices[entity];
                            const T& cmd = Commands[idx];

                            U data =
                            {
                                entity->WorldTransform().ToMatrix4x4(),
                                entity->PrimaryColor(),
                            };
                            Entities.Set(cmd.FirstInstance, data);
                        }

                        Entities.Update();
                    }
                    
                    ToUpdate.clear();
                    _needsReallocation = false;
                    _needsUpdate = false;
                }
                void Update(const IRenderable3D<V>& entity)
                {
                    if (!EntityIndices.count(&entity)) { return; }

                    const auto& components = entity.Components();
                    for (uint a = 0; a < components.Count(); a++)
                        Update(*components(a));

                    ToUpdate.insert(&entity);
                    _needsUpdate = true;
                }



                /** BINDING UTILITIES **/
                void Bind(int slot = 0)         const override
                {
                    BindEntity(slot);
                    BindResources();
                }
                /// <summary> Binds the command, per-entity, vertex, and index buffers to the GPU. </summary>
                /// <param name="slot"> The buffer binding index at which buffers will be attached to the GPU. </param>
                void BindEntity(int slot = 0)   const override
                {
                    Commands.Bind(slot);
                    Entities.Bind(slot);
                    Vertices.Bind(slot);

                    if (!Indices.IsEmpty())
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
                


            protected:

                /** PROPERTY DATA **/
                bool                                        _needsReallocation;
                bool                                        _needsUpdate;



                /** DATA COLLECTIONS **/
                /// <summary> A collection of indirect drawing commands used to render geometry on the GPU. </summary>
                CommandBuffer<T>                            Commands;
                /// <summary> A collection of uniform data that describes the appearance of rendered geometry on the GPU. </summary>
                UniformBuffer<U>                            Entities;
                /// <summary> A collection of vertices used to build geometry on the GPU. </summary>
                VertexBuffer<V>                             Vertices;
                /// <summary> A collection of indices that dictate the vertex drawing order. </summary>
                IndexBuffer                                 Indices;

                std::map<const IRenderable3D<V>*, uint>     EntityIndices;

                std::set<const IRenderable3D<V>*>           ToUpdate;



                /** UTILITIES **/
                void AddCommand(const IRenderable3D<V>* entity)
                {
                    uint nVertices = entity->Indices().IsEmpty() ? entity->Points().Count() : entity->Indices().Count();
                    Commands.Add(T(nVertices, 1, Indices.Count(), Vertices.Count(), Commands.Count()));
                }
                void AddEntity(const IRenderable3D<V>* entity)
                {
                    U data =
                    {
                        entity->WorldTransform().ToMatrix4x4(),
                        entity->PrimaryColor(),
                    };
                    Entities.Add(data);
                }
                void AddVertices(const IRenderable3D<V>* entity)
                {
                    const Vector<V>& vertices = entity->Points();
                    for (uint a = 0; a < vertices.Count(); a++)
                        Vertices.Add(vertices(a));

                    const Vector<uint>& indices = entity->Indices();
                    for (uint a = 0; a < indices.Count(); a++)
                        Indices.Add(indices(a));
                }
                void ClearBuffers()
                {
                    Commands.Clear();
                    Entities.Clear();
                    Vertices.Clear();
                    Indices.Clear();

                    _needsReallocation = true;
                    _needsUpdate = true;
                }

        };




    }
}