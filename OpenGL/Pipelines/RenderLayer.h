/* CHANGELOG
 * Written by Josh Grooms on 20161222
 */

#pragma once
#include "Collections/BST.h"
#include "Pipelines/RenderStage3D.h"



namespace Cyclone
{
    namespace OpenGL
    {
        struct BufferIndices;

        class IRenderLayer
        {

            public:

                virtual const string& Name()                const = 0;
                virtual List<IRenderStage*> Stages()        const = 0;
                virtual const GraphicsSettings& Settings()  const = 0;

                virtual ~IRenderLayer() { }

                virtual void Add(const string& name, const IRenderStage& stage)             = 0;
                virtual void Associate(const string& stage, const BufferIndices& indices)   = 0;
                virtual void Dissociate(const string& stage, const BufferIndices& indices)  = 0;
                virtual void Remove(const string& name)                                     = 0;
                virtual void Update()                                                       = 0;
        };


        class RenderLayer : public IRenderLayer
        {
            public:

                virtual const string& Name()                    const { return _name; }
                virtual const GraphicsSettings& Settings()      const { return _settings; }

            protected:

                RenderLayer(const string& name = "") : 
                    _name(name)
                {

                }

            private:
                
                string              _name;
                GraphicsSettings    _settings;


        };


        struct StagePair3D
        {
            RenderStage3D<IndexedDrawCommand>   Indexed;
            RenderStage3D<DrawCommand>          NonIndexed;
        };


        class RenderGroup3D
        {
            public:


            private:

                BST<VertexTopologies, StagePair3D*>     _stages;

        };



        class RenderLayer3D : public RenderLayer
        {

            public:

                OpenGLAPI List<IRenderStage*> Stages() const override;



                OpenGLAPI void Add(const string& name, const IRenderStage& stage)               override;
                OpenGLAPI void Associate(const string& stage, const BufferIndices& indices)     override;
                OpenGLAPI void Dissociate(const string& stage, const BufferIndices& indices)    override;
                OpenGLAPI void Remove(const string& stage)                                      override;
                OpenGLAPI void Update()                                                         override;


            private:

                BST<string, RenderGroup3D*> _stages;
                
        };
    }
}
