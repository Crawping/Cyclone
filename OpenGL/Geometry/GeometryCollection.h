/* CHANGELOG
 * Written by Josh Grooms on 20160823
 */

#pragma once
#include "EnumerationsGL.h"
#include "Buffers/DrawBuffer.h"
#include "Interfaces/IGraphicsBuffer.h"
#include <map>



namespace Cyclone
{
    namespace OpenGL
    {

        class GeometryCollection
        {
            
            public:
                uint Count()                    const { return Buffers.size(); }
                bool NeedsUpdate()              const { return _needsUpdate; }



                /** CONSTRUCTOR **/
                OpenGLAPI GeometryCollection();



                /** PUBLIC UTILITIES **/
                OpenGLAPI void Add(const IRenderableEntity& entity);
                OpenGLAPI void Clear();
                OpenGLAPI void Remove(const IRenderableEntity& entity);
                OpenGLAPI void Update();


                OpenGLAPI void Bind(VertexTopologies topology) const;


                /** BINDING UTILITLIES **/
                //void Bind(int slot = 0)         const override;
                //void BindEntity(int slot = 0)   const override;
                //void BindResources()            const override;

                //void Unbind()                   const override;
                //void UnbindEntity()             const override;
                //void UnbindResources()          const override;

                


            private:
                bool _needsUpdate;

                std::map<VertexTopologies, DrawBuffer>  Buffers;
                std::set<const IRenderableEntity*>      Entities;

        };

    }
}