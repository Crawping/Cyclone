#include "Scenes/Scene3D.h"
#include "Scenes/SceneComponent3D.h"
#include "Pipelines/RenderStage3D.h"


namespace Cyclone
{
    namespace OpenGL
    {
        /** INTERNAL CLASSES **/
        struct StageGroup3D
        {
            RenderStage3D<IndexedDrawCommand>   Indexed;
            RenderStage3D<DrawCommand>          NonIndexed;
        };



        /** PROPERTIES **/
        List<IRenderStage&> SceneComponent3D::Stages() const
        {
            List<IRenderStage&> stages;
            if (!IsVisible()) { return stages; }

            for (auto* group : Staging.Values())
            {
                stages.Append(group->Indexed);
                stages.Append(group->NonIndexed);
            }

            return stages;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        SceneComponent3D::SceneComponent3D(const string& name, ISceneLayer& parent) :
            SceneComponent(name, parent)
        {

        }
        SceneComponent3D::~SceneComponent3D()
        {
            for (auto* stage : Staging.Values())
                delete stage;
        }



        /** UTILITIES **/
        void SceneComponent3D::Insert(const IRenderable& entity)
        {
            ResourceMapping& map = Register(entity);
            Resources.Insert(&map);
            SceneComponent::Insert(entity);
        }
        void SceneComponent3D::Update()
        {
            if (!NeedsUpdate()) { return; }

            ClearCommands();

            for (const auto* ids : Resources)
            {
                StageGroup3D* stage;
                if (Staging.Contains(ids->Topology))
                    stage = Staging[ids->Topology];
                else
                    stage = CreateStage(ids->Topology);

                if (ids->IndicesCount)
                    stage->Indexed.Add(IndexedDrawCommand(ids->IndicesCount, 1, ids->IndicesIndex, ids->VertexIndex, ids->EntityKey.Index()));
                else
                    stage->NonIndexed.Add(DrawCommand(ids->VertexCount, 1, 0, ids->VertexIndex, ids->EntityKey.Index()));
            }

            for (auto* stage : Staging.Values())
            {
                stage->Indexed.Update();
                stage->NonIndexed.Update();
            }

            SceneComponent::Update();
        }



        /** PRIVATE UTILITIES **/
        void SceneComponent3D::ClearCommands()
        {
            for (auto* stage : Staging.Values())
            {
                stage->Indexed.ClearCommands();
                stage->NonIndexed.ClearCommands();
            }

            NeedsUpdate(true);
        }
        void SceneComponent3D::ClearMappings()
        {
            Resources.Clear();
            NeedsUpdate(true);
        }
        StageGroup3D* SceneComponent3D::CreateStage(VertexTopologies topology)
        {
            StageGroup3D* stage = new StageGroup3D();
            stage->Indexed
                .Settings(Settings())
                .Topology(topology);

            stage->NonIndexed
                .Settings(Settings())
                .Topology(topology);

            Staging.Insert(topology, stage);
            return stage;
        }
        



    }
}