/* CHANGELOG 
 * Written by Josh Grooms on 20161012
 */

#pragma once
#include "SVGAPI.h"
#include "Buffers/UniformBuffer.h"
#include "Imaging/Color4.h"
#include "Interfaces/IRenderable2D.h"
#include <map>
#include <set>



namespace Cyclone
{
    namespace { using namespace OpenGL; }
    namespace SVG
    {
        class DrawBuffer2D : public IGraphicsBuffer
        {
            public:
                
                List<const IRenderable2D<float>*> Entities() const;


                uint Count()        const override { return EntityIndices.size(); }
                uint ID()           const override { return ColorBuffer.ID(); }
                bool NeedsUpdate()  const override { return _needsUpdate || _needsReallocation; }



                /** CONSTRUCTOR **/
                SVGAPI DrawBuffer2D();
                SVGAPI DrawBuffer2D(DrawBuffer2D&& other) = delete;
                SVGAPI DrawBuffer2D(const DrawBuffer2D& other) = delete;



                /** BUFFER UTILITIES **/
                SVGAPI void Add(const IRenderable2D<float>& entity);
                SVGAPI void Clear() override;
                SVGAPI void Remove(const IRenderable2D<float>& entity);



                /** BINDING UTILITIES **/
                SVGAPI void Bind(int slot = 0)          const override { BindEntity(); BindResources(); }
                SVGAPI void BindEntity(int slot = 0)    const override { ColorBuffer.BindEntity(); }
                SVGAPI void BindResources()             const override { ColorBuffer.BindResources(); }

                SVGAPI void Unbind()            const override { UnbindEntity(); UnbindResources(); }
                SVGAPI void UnbindEntity()      const override { ColorBuffer.UnbindEntity(); }
                SVGAPI void UnbindResources()   const override { ColorBuffer.UnbindResources(); }

                SVGAPI void Update() override;
                SVGAPI void Update(const IRenderable2D<float>& entity);

            private:
            
                bool _needsReallocation;
                bool _needsUpdate;

                UniformBuffer<Color4>                           ColorBuffer;
                std::map<const IRenderable2D<float>*, uint>     EntityIndices;
                std::set<const IRenderable2D<float>*>           ToUpdate;


                void Add(const IRenderable3D<float>* entity);
                void Update(const IRenderable3D<float>* entity);
                


        };
    }
}
