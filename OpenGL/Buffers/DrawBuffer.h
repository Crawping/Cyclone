/* CHANGELOG
 * Written by Josh Grooms on 20160821
 */

#pragma once
#include "Buffers/CommandBuffer.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/UniformData.h"
#include "Buffers/VertexBuffer.h"
#include "Interfaces/IUpdatable.h"
#include <set>



namespace Cyclone
{
    namespace OpenGL
    {
        class IRenderableEntity;

        class DrawBuffer : public IBindable, public IUpdatable
        {
            public:
                
                /** PROPERTIES **/
                uint Count()                    const { return Commands.Count(); }
                uint ID()                       const override { return 0; }
                bool NeedsUpdate()              const override { return _needsUpdate; }
                VertexTopologies Topology()     const { return _topology; }



                /** CONSTRUCTOR **/
                OpenGLAPI DrawBuffer();



                /** BUFFER UTILITIES **/
                OpenGLAPI void Add(const IRenderableEntity& entity);
                OpenGLAPI void Clear();
                OpenGLAPI void Remove(const IRenderableEntity& entity);


                /** BINDING UTILITIES **/
                OpenGLAPI void Bind(int slot = 0)             const override;
                OpenGLAPI void BindEntity(int slot = 0)       const override;
                OpenGLAPI void BindResources()                const override;

                OpenGLAPI void Unbind()                       const override;
                OpenGLAPI void UnbindEntity()                 const override;
                OpenGLAPI void UnbindResources()              const override;

                OpenGLAPI void Update()                       override;



            private:
                bool                        _needsUpdate;
                VertexTopologies            _topology;

                CommandBuffer               Commands;
                UniformBuffer<PerEntity>    Entities;
                VertexBuffer                Vertices;

                std::set<const IRenderableEntity*> ExistingEntities;


                void AddCommand(const IRenderableEntity* entity);
                void AddEntity(const IRenderableEntity* entity);
                void AddVertices(const IRenderableEntity* entity);
        };
    }
}