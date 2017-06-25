#include "Collections/List.h"
#include "Interfaces/IGeometric.h"
#include "Interfaces/IGraphicsBuffer.h"
#include "Interfaces/IModel.h"
#include "Interfaces/IRenderable.h"
#include "Interfaces/ITexture.h"
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
        List<BufferBinding> SceneComponent3D::Buffers() const
        {
            return
            {
                { _geometry,     0 },
                { _resources,    2 },
            };
        }
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
            SceneComponent(name, parent),
            NeedsUpdate(false)
        {

        }
        SceneComponent3D::~SceneComponent3D()
        {
            for (auto* stage : Staging.Values())
                delete stage;
        }



        /** UTILITIES **/
        void SceneComponent3D::Insert(const Resource<IRenderable>& entity)
        {
            if (entity.IsNull() || _entities.Contains(entity.ID())) { return; }
            _entities.Insert(entity.ID(), entity);
            Parent().Insert(entity);
            NeedsUpdate = true;
        }
        void SceneComponent3D::Update()
        {
            if (!NeedsUpdate) { return; }

            ClearCommands();
            _geometry.Clear();

            for (uint a = 0; a < _entities.Count(); a++)
            {
                const auto& entity = _entities(a);
                uint idxEntity = Parent().IndexOf(entity);

                _resources.Set(entity.ID(), { Parent().IndexOf(entity->Material()), idxEntity });

                const auto& model = entity->Model();
                const auto& geometry = model->Geometry();
                if (model.IsNull() || geometry.IsNull()) { continue; }

                const auto& indices = geometry->Indices();
                const auto& vertices = geometry->Vertices();

                StageGroup3D* stage;
                PointTopologies topology = geometry->Topology();

                if (Staging.Contains(topology))
                    stage = Staging[topology];
                else
                    stage = CreateStage(topology);

                if (indices.IsEmpty())
                    stage->NonIndexed.Append(DrawCommand(vertices.Count(), 1, 0, _geometry.PointCount(), idxEntity));
                else
                    stage->Indexed.Append(IndexedDrawCommand(indices.Count(), 1, _geometry.IndexCount(), _geometry.PointCount(), idxEntity));

                _geometry.Append(indices);
                _geometry.Append(vertices);
            }
            
            for (auto* stage : Staging.Values())
            {
                stage->Indexed.Update();
                stage->NonIndexed.Update();
            }

            _geometry.Update();
            _resources.Update();

            NeedsUpdate = false;
        }
        void SceneComponent3D::Update(const Resource<IRenderable>& entity)
        {
            if (!_entities.Contains(entity.ID())) { return; }
            Parent().Update(entity);
        }



        /** PROTECTED UTILITIES **/
        void SceneComponent3D::UpdateGeometry(const Resource<IRenderable>& entity)
        {
            if ( entity.IsNull() || entity->Model().IsNull() || entity->Model()->Geometry().IsNull() )
                return;


        }



        /** PRIVATE UTILITIES **/
        void SceneComponent3D::ClearCommands()
        {
            for (auto* stage : Staging.Values())
            {
                stage->Indexed.ClearCommands();
                stage->NonIndexed.ClearCommands();
            }

            NeedsUpdate = true;
        }
        StageGroup3D* SceneComponent3D::CreateStage(PointTopologies topology)
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