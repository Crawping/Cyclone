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


        List<BufferBinding> RenderStage2D::Buffers() const
        {
            return { { *_data, 0 } };
        }


        /** CONSTRUCTOR **/
        RenderStage2D::RenderStage2D(const DrawBuffer2D* data, const GraphicsSettings* settings) :
            _data(data),
            _settings(settings)
        {

        }


        void RenderStage2D::Render() const
        {
            int idx = 0;
            int drawID = GetUniformID("DrawID");
            int colorID = GetResourceID("InputColor");
            auto entities = _data->Entities();

            for (uint a = 0; a < entities.Count(); a++)
            {
                nvMatrixLoadf(TransformMatrices::ModelView, entities(a)->WorldTransform().ToMatrix4x4().ToArray());
                SetResource(colorID, entities(a)->PrimaryColor());
                SetUniform(drawID, idx++);
                entities(a)->Fill();
                SetUniform(drawID, idx++);
                entities(a)->Stroke();
            }
        }


        int RenderStage2D::GetResourceID(const string& name) const
        {
            if (Settings().Pipeline)
                return glGetProgramResourceLocation(Settings().Pipeline->ID(), GL_FRAGMENT_INPUT_NV, name.c_str());
            else
                return -1;
        }
        int RenderStage2D::GetUniformID(const string& name) const
        {
            if (Settings().Pipeline)
                return glGetUniformLocation(Settings().Pipeline->ID(), name.c_str());
            else
                return -1;
        }
        void RenderStage2D::SetResource(int id, const Color4& value) const
        {
            Vector<float, 12> color =
            {
                0, 0, value.R,
                0, 0, value.G,
                0, 0, value.B,
                value.A / 2.0f, value.A / 2.0f, 0,
            };

            nvProgramPathFragmentInputGen
            (
                Settings().Pipeline->ID(),
                id,
                GenerationModes::ObjectBoundingBox,
                4,
                &color(0)
            );
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
