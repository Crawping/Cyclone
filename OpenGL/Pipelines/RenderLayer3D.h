/* CHANGELOG
 * Written by Josh Grooms on 20161223
 */

#pragma once
#include "Collections/BST.h"
#include "Interfaces/IRenderLayer.h"
#include "Pipelines/RenderStage3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        class RenderGroup3D;

        class RenderLayer3D : public IRenderLayer
        {

            public:

                /** PROPERTIES **/
                OpenGLAPI List<IRenderStage*> Stages() const override;



                /** CONSTRUCTOR & DESTRUCTOR **/
                OpenGLAPI RenderLayer3D();
                OpenGLAPI ~RenderLayer3D();



                /** UTILITIES **/
                OpenGLAPI void Add(const string& name, const GraphicsSettings& stage)               override;
                OpenGLAPI void Associate(const string& stageName, const ResourceMapping& indices)   override;
                OpenGLAPI void Dissociate(const string& stageName, const ResourceMapping& indices)  override;
                OpenGLAPI void Remove(const string& stageName)                                      override;
                OpenGLAPI void Update()                                                             override;


            private:

                BST<string, RenderGroup3D*> _stages;

        };
    }
}
