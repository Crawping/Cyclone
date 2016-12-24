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
            for (auto* group : Staging.Values())
            {
                stages.Append(group->Indexed);
                stages.Append(group->NonIndexed);
            }

            return stages;
        }

        SceneComponent3D& SceneComponent3D::Settings(const GraphicsSettings& value) 
        { 
            _settings = value; 
            return *this; 
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        SceneComponent3D::SceneComponent3D() :
            _needsUpdate(false)
        {

        }
        SceneComponent3D::~SceneComponent3D()
        {
            for (auto* stage : Staging.Values())
                delete stage;
        }



        /** UTILITIES **/
        void SceneComponent3D::Insert(const ResourceMapping& indices)
        {
            Resources.Insert(&indices);
            _needsUpdate = true;
        }
        void SceneComponent3D::ClearCommands()
        {
            for (auto* stage : Staging.Values())
            {
                stage->Indexed.ClearCommands();
                stage->NonIndexed.ClearCommands();
            }

            _needsUpdate = true;
        }
        void SceneComponent3D::ClearMappings()
        {
            Resources.Clear();
            _needsUpdate = true;
        }
        void SceneComponent3D::Remove(const ResourceMapping& indices)
        {
            Resources.Remove(&indices);
            _needsUpdate = true;
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
                    stage->Indexed.Add(IndexedDrawCommand(ids->IndicesCount, 1, ids->IndicesIndex, ids->VertexIndex, ids->EntityIndex));
                else
                    stage->NonIndexed.Add(DrawCommand(ids->VertexCount, 1, 0, ids->VertexIndex, ids->EntityIndex));
            }

            for (auto* stage : Staging.Values())
            {
                stage->Indexed.Update();
                stage->NonIndexed.Update();
            }

            _needsUpdate = false;
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
            //Staging[topology] = stage;
            return stage;
        }
        
    }
}