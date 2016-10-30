#include "EnumerationsSVG.h"
#include "NVPR.h"
#include "GraphicsSettings.h"
#include "RenderStage2D.h"
#include "Buffers/DrawBuffer2D.h"
#include "Interfaces/IGraphicsBuffer.h"
#include "Interfaces/ITransformation3D.h"
#include "Pipelines/GraphicsPipeline.h"



namespace Cyclone
{
    namespace SVG
    {

        /** CONSTRUCTOR **/
        RenderStage2D::RenderStage2D(const DrawBuffer2D* data, const GraphicsSettings* settings) :
            _data(data),
            _settings(settings)
        {

        }


        void RenderStage2D::Render()
        {
            int idx = 0;
            int drawID = GetUniformID("DrawID");
            auto entities = _data->Entities();

            for (uint a = 0; a < entities.Count(); a++)
            {
                nvMatrixLoadf(TransformMatrices::ModelView, entities(a)->World().ToMatrix4x4().ToArray());
                SetUniform(drawID, idx++);
                entities(a)->Fill();
                SetUniform(drawID, idx++);
                entities(a)->Stroke();
            }
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
        void RenderStage2D::SetUniform(int id, const Color4& value)               const
        {
            glUniform4f(id, value.R, value.G, value.B, value.A);
        }
    }
}
