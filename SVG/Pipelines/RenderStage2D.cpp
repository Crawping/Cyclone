#include "EnumerationsSVG.h"
#include "NVPR.h"
#include "GraphicsSettings.h"
#include "Interfaces/IGraphicsBuffer.h"
#include "Interfaces/IMaterial.h"
#include "Interfaces/IRenderable2D.h"
#include "Interfaces/ITransformable.h"
#include "Interfaces/ISpatialTransform.h"
#include "Models/Model3D.h"
#include "Pipelines/GraphicsPipeline.h"
#include "Pipelines/RenderStage2D.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace SVG
    {

        /** CONSTRUCTOR **/
        RenderStage2D::RenderStage2D()
        {

        }



        /** UTILITIES **/
        void RenderStage2D::ClearEntities()
        {
            Entities.Clear();
        }
        void RenderStage2D::Insert(uint drawID, const IRenderable2D& entity)
        {
            Entities.Insert(&entity, drawID);
        }
        void RenderStage2D::Remove(const IRenderable2D& entity)
        {
            Entities.Remove(&entity);
        }
        void RenderStage2D::Render()                                    const
        {
            int idx = 0;
            int drawID = GetUniformID("DrawID");
            int colorID = GetResourceID("InputColor");

            auto keys = Entities.Keys();
            auto vals = Entities.Values();

            for (uint a = 0; a < Entities.Count(); a++)
            {
                //const auto& world = keys(a)->Transforms().World();
                const auto& world = keys(a)->Model().Transform();
                nvMatrixLoadf(TransformMatrices::ModelView, world.ToMatrix4x4().ToArray());

                SetResource(colorID, keys(a)->Material().PrimaryColor());
                SetUniform(drawID, 2 * vals(a));
                keys(a)->Fill();
                SetUniform(drawID, 2 * vals(a) + 1);
                keys(a)->Stroke();
            }
        }

        int RenderStage2D::GetResourceID(const string& name)            const
        {
            if (Settings().Pipeline)
                return glGetProgramResourceLocation(Settings().Pipeline->ID(), GL_FRAGMENT_INPUT_NV, name.c_str());
            else
                return -1;
        }
        int RenderStage2D::GetUniformID(const string& name)             const
        {
            if (Settings().Pipeline)
                return glGetUniformLocation(Settings().Pipeline->ID(), name.c_str());
            else
                return -1;
        }
        void RenderStage2D::SetResource(int id, const Color4& value)    const
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
        void RenderStage2D::SetUniform(int id, int value)               const
        {
            glUniform1i(id, value);
        }
        void RenderStage2D::SetUniform(int id, const Color4& value)     const
        {
            glUniform4f(id, value.R, value.G, value.B, value.A);
        }

    }
}
