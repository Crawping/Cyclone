#include "Collections/Set.h"
#include "Pipelines/RenderLayer3D.h"
#include "Scenes/Scene3D.h"



namespace Cyclone
{
    namespace OpenGL
    {

        /** INTERNAL CLASSES **/
        struct StagePair3D
        {
            RenderStage3D<IndexedDrawCommand>   Indexed;
            RenderStage3D<DrawCommand>          NonIndexed;
        };

        class RenderGroup3D
        {
            public:

                /** PROPERTIES **/
                List<IRenderStage*> Stages() const
                {
                    List<IRenderStage*> stages;
                    for (auto* group : _stages.Values())
                    {
                        stages.Append(&(group->Indexed));
                        stages.Append(&(group->NonIndexed));
                    }

                    return stages;
                }

                const GraphicsSettings& Settings()  const { return _settings; }
                bool NeedsUpdate()                  const { return _needsUpdate; }


                RenderGroup3D& Settings(const GraphicsSettings& value) { _settings = value; return *this; }



                /** CONSTRUCTOR & DESTRUCTOR **/
                RenderGroup3D() :
                    _needsUpdate(false)
                {

                }
                ~RenderGroup3D()
                {
                    for (auto* stage : _stages.Values())
                        delete stage;
                }



                /** UTILITIES **/
                void Add(const ResourceMapping& indices)
                {
                    Mappings.Insert(&indices);
                    _needsUpdate = true;
                }
                void ClearCommands()
                {
                    for (auto* stage : _stages.Values())
                    {
                        stage->Indexed.ClearCommands();
                        stage->NonIndexed.ClearCommands();
                    }

                    _needsUpdate = true;
                }
                void ClearMappings()
                {
                    Mappings.Clear();
                    _needsUpdate = true;
                }
                void Remove(const ResourceMapping& indices)
                {
                    Mappings.Remove(&indices);
                    _needsUpdate = true;
                }
                void Update()
                {
                    if (!NeedsUpdate()) { return; }

                    ClearCommands();

                    for (const auto* ids : Mappings)
                    {
                        StagePair3D* stage = _stages.Contains(ids->Topology) ?
                            _stages[ids->Topology] : CreateStage(ids->Topology);

                        if (ids->IndicesCount)
                            stage->Indexed.Add(IndexedDrawCommand(ids->IndicesCount, 1, ids->IndicesIndex, ids->VertexIndex, ids->EntityIndex));
                        else
                            stage->NonIndexed.Add(DrawCommand(ids->VertexCount, 1, 0, ids->VertexIndex, ids->EntityIndex));
                    }

                    for (auto* stage : _stages.Values())
                    {
                        stage->Indexed.Update();
                        stage->NonIndexed.Update();
                    }

                    _needsUpdate = false;
                }

            private:

                bool                                    _needsUpdate;
                GraphicsSettings                        _settings;
                BST<VertexTopologies, StagePair3D*>     _stages;

                Set<const ResourceMapping*>             Mappings;

                StagePair3D* CreateStage(VertexTopologies topology)
                {
                    StagePair3D* stage = _stages[topology] = new StagePair3D();
                    stage->Indexed.Topology(topology);
                    stage->NonIndexed.Topology(topology);
                    return stage;
                }

        };



        /** PROPERTIES **/
        List<IRenderStage*> RenderLayer3D::Stages() const
        {
            List<IRenderStage*> stages;
            for (auto* group : _stages.Values())
                stages.Append(group->Stages());

            return stages;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        RenderLayer3D::RenderLayer3D()
        {

        }
        RenderLayer3D::~RenderLayer3D()
        {
            for (auto* group : _stages.Values())
                delete group;
        }



        /** UTILITIES **/
        void RenderLayer3D::Add(const string& name, const GraphicsSettings& stage)
        {
            if (!_stages.Contains(name))
                _stages[name] = new RenderGroup3D();

            _stages[name]->Settings(stage);
        }
        void RenderLayer3D::Associate(const string& stageName, const ResourceMapping& indices)
        {
            if (!_stages.Contains(stageName)) { return; }
            _stages[stageName]->Add(indices);
        }
        void RenderLayer3D::Dissociate(const string& stageName, const ResourceMapping& indices)
        {
            if (!_stages.Contains(stageName)) { return; }
            _stages[stageName]->Remove(indices);
        }
        void RenderLayer3D::Remove(const string& stageName)
        {
            if (!_stages.Contains(stageName)) { return; }

            delete _stages[stageName];
            _stages.Remove(stageName);
        }
        void RenderLayer3D::Update()
        {
            for (auto* group : _stages.Values())
                group->Update();
        }

    }
}