#include "EnumerationsSVG.h"
#include "NVPR.h"
#include "GraphicsSettings.h"
#include "RenderStage2D.h"
#include "Interfaces/IGraphicsBuffer.h"
#include "Interfaces/ITransformation3D.h"
#include "Pipelines/GraphicsPipeline.h"

//using namespace Cyclone::OpenGL;



namespace Cyclone
{
    namespace SVG
    {

        /** CONSTRUCTOR **/
        RenderStage2D::RenderStage2D(const UniformBuffer<Color4>* data, const std::set< const IRenderable2D<float>* >* entities, const GraphicsSettings* settings) : 
            _data(data),
            _settings(settings),
            Entities(entities)
        {

        }


        void RenderStage2D::Render()
        {
            if (!Entities->size()) { return; }

            glStencilMask(~0);
            glEnable(GL_STENCIL_TEST);
            glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
            glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);

            int drawID = GetUniformID("DrawID");
            
            int idx = 0;
            for (const auto* e : *Entities)
            {
                nvMatrixLoadf(TransformMatrices::ModelView, e->World().ToMatrix4x4().ToArray());
                SetUniform(drawID, idx++);
                e->Fill();
                SetUniform(drawID, idx++);
                e->Stroke();
            }

            glDisable(GL_STENCIL_TEST);
        }
        


        int RenderStage2D::GetUniformID(const string& name)                                   const
        {
            if (Settings() && Settings()->Pipeline)
                return glGetUniformLocation(Settings()->Pipeline->ID(), name.c_str());
            else
                return -1;
        }
        void RenderStage2D::SetUniform(int id, int value) const
        {
            glUniform1i(id, value);
        }
        void RenderStage2D::SetUniform(const string& name, const Color4& value)               const
        {
            int varID = GetUniformID(name);
            if (varID != -1)
                glUniform4f(varID, value.R, value.G, value.B, value.A);
        }
    }
}